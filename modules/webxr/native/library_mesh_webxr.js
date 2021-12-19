/*************************************************************************/
/*  library_mesh_webxr.js                                               */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           MESH ENGINE                                */
/*                      https://mesh-engine.com                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Mesh Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
const MeshWebXR = {
	$MeshWebXR__deps: ['$Browser', '$GL', '$MeshRuntime'],
	$MeshWebXR: {
		gl: null,

		texture_ids: [null, null],
		textures: [null, null],

		session: null,
		space: null,
		frame: null,
		pose: null,

		// Monkey-patch the requestAnimationFrame() used by Emscripten for the main
		// loop, so that we can swap it out for XRSession.requestAnimationFrame()
		// when an XR session is started.
		orig_requestAnimationFrame: null,
		requestAnimationFrame: (callback) => {
			if (MeshWebXR.session && MeshWebXR.space) {
				const onFrame = function (time, frame) {
					MeshWebXR.frame = frame;
					MeshWebXR.pose = frame.getViewerPose(MeshWebXR.space);
					callback(time);
					MeshWebXR.frame = null;
					MeshWebXR.pose = null;
				};
				MeshWebXR.session.requestAnimationFrame(onFrame);
			} else {
				MeshWebXR.orig_requestAnimationFrame(callback);
			}
		},
		monkeyPatchRequestAnimationFrame: (enable) => {
			if (MeshWebXR.orig_requestAnimationFrame === null) {
				MeshWebXR.orig_requestAnimationFrame = Browser.requestAnimationFrame;
			}
			Browser.requestAnimationFrame = enable
				? MeshWebXR.requestAnimationFrame : MeshWebXR.orig_requestAnimationFrame;
		},
		pauseResumeMainLoop: () => {
			// Once both MeshWebXR.session and MeshWebXR.space are set or
			// unset, our monkey-patched requestAnimationFrame() should be
			// enabled or disabled. When using the WebXR API Emulator, this
			// gets picked up automatically, however, in the Oculus Browser
			// on the Quest, we need to pause and resume the main loop.
			Browser.mainLoop.pause();
			window.setTimeout(function () {
				Browser.mainLoop.resume();
			}, 0);
		},

		// Some custom WebGL code for blitting our eye textures to the
		// framebuffer we get from WebXR.
		shaderProgram: null,
		programInfo: null,
		buffer: null,
		// Vertex shader source.
		vsSource: `
			const vec2 scale = vec2(0.5, 0.5);
			attribute vec4 aVertexPosition;

			varying highp vec2 vTextureCoord;

			void main () {
				gl_Position = aVertexPosition;
				vTextureCoord = aVertexPosition.xy * scale + scale;
			}
		`,
		// Fragment shader source.
		fsSource: `
			varying highp vec2 vTextureCoord;

			uniform sampler2D uSampler;

			void main() {
				gl_FragColor = texture2D(uSampler, vTextureCoord);
			}
		`,

		initShaderProgram: (gl, vsSource, fsSource) => {
			const vertexShader = MeshWebXR.loadShader(gl, gl.VERTEX_SHADER, vsSource);
			const fragmentShader = MeshWebXR.loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

			const shaderProgram = gl.createProgram();
			gl.attachShader(shaderProgram, vertexShader);
			gl.attachShader(shaderProgram, fragmentShader);
			gl.linkProgram(shaderProgram);

			if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
				MeshRuntime.error(`Unable to initialize the shader program: ${gl.getProgramInfoLog(shaderProgram)}`);
				return null;
			}

			return shaderProgram;
		},
		loadShader: (gl, type, source) => {
			const shader = gl.createShader(type);
			gl.shaderSource(shader, source);
			gl.compileShader(shader);

			if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
				MeshRuntime.error(`An error occurred compiling the shader: ${gl.getShaderInfoLog(shader)}`);
				gl.deleteShader(shader);
				return null;
			}

			return shader;
		},
		initBuffer: (gl) => {
			const positionBuffer = gl.createBuffer();
			gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
			const positions = [
				-1.0, -1.0,
				1.0, -1.0,
				-1.0, 1.0,
				1.0, 1.0,
			];
			gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
			return positionBuffer;
		},
		blitTexture: (gl, texture) => {
			if (MeshWebXR.shaderProgram === null) {
				MeshWebXR.shaderProgram = MeshWebXR.initShaderProgram(gl, MeshWebXR.vsSource, MeshWebXR.fsSource);
				MeshWebXR.programInfo = {
					program: MeshWebXR.shaderProgram,
					attribLocations: {
						vertexPosition: gl.getAttribLocation(MeshWebXR.shaderProgram, 'aVertexPosition'),
					},
					uniformLocations: {
						uSampler: gl.getUniformLocation(MeshWebXR.shaderProgram, 'uSampler'),
					},
				};
				MeshWebXR.buffer = MeshWebXR.initBuffer(gl);
			}

			const orig_program = gl.getParameter(gl.CURRENT_PROGRAM);
			gl.useProgram(MeshWebXR.shaderProgram);

			gl.bindBuffer(gl.ARRAY_BUFFER, MeshWebXR.buffer);
			gl.vertexAttribPointer(MeshWebXR.programInfo.attribLocations.vertexPosition, 2, gl.FLOAT, false, 0, 0);
			gl.enableVertexAttribArray(MeshWebXR.programInfo.attribLocations.vertexPosition);

			gl.activeTexture(gl.TEXTURE0);
			gl.bindTexture(gl.TEXTURE_2D, texture);
			gl.uniform1i(MeshWebXR.programInfo.uniformLocations.uSampler, 0);

			gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);

			// Restore state.
			gl.bindTexture(gl.TEXTURE_2D, null);
			gl.disableVertexAttribArray(MeshWebXR.programInfo.attribLocations.vertexPosition);
			gl.bindBuffer(gl.ARRAY_BUFFER, null);
			gl.useProgram(orig_program);
		},

		// Holds the controllers list between function calls.
		controllers: [],

		// Updates controllers array, where the left hand (or sole tracker) is
		// the first element, and the right hand is the second element, and any
		// others placed at the 3rd position and up.
		sampleControllers: () => {
			if (!MeshWebXR.session || !MeshWebXR.frame) {
				return;
			}

			let other_index = 2;
			const controllers = [];
			MeshWebXR.session.inputSources.forEach((input_source) => {
				if (input_source.targetRayMode === 'tracked-pointer') {
					if (input_source.handedness === 'right') {
						controllers[1] = input_source;
					} else if (input_source.handedness === 'left' || !controllers[0]) {
						controllers[0] = input_source;
					}
				} else {
					controllers[other_index++] = input_source;
				}
			});
			MeshWebXR.controllers = controllers;
		},

		getControllerId: (input_source) => MeshWebXR.controllers.indexOf(input_source),
	},

	mesh_webxr_is_supported__proxy: 'sync',
	mesh_webxr_is_supported__sig: 'i',
	mesh_webxr_is_supported: function () {
		return !!navigator.xr;
	},

	mesh_webxr_is_session_supported__proxy: 'sync',
	mesh_webxr_is_session_supported__sig: 'vii',
	mesh_webxr_is_session_supported: function (p_session_mode, p_callback) {
		const session_mode = MeshRuntime.parseString(p_session_mode);
		const cb = MeshRuntime.get_func(p_callback);
		if (navigator.xr) {
			navigator.xr.isSessionSupported(session_mode).then(function (supported) {
				const c_str = MeshRuntime.allocString(session_mode);
				cb(c_str, supported ? 1 : 0);
				MeshRuntime.free(c_str);
			});
		} else {
			const c_str = MeshRuntime.allocString(session_mode);
			cb(c_str, 0);
			MeshRuntime.free(c_str);
		}
	},

	mesh_webxr_initialize__deps: ['emscripten_webgl_get_current_context'],
	mesh_webxr_initialize__proxy: 'sync',
	mesh_webxr_initialize__sig: 'viiiiiiiiii',
	mesh_webxr_initialize: function (p_session_mode, p_required_features, p_optional_features, p_requested_reference_spaces, p_on_session_started, p_on_session_ended, p_on_session_failed, p_on_controller_changed, p_on_input_event, p_on_simple_event) {
		MeshWebXR.monkeyPatchRequestAnimationFrame(true);

		const session_mode = MeshRuntime.parseString(p_session_mode);
		const required_features = MeshRuntime.parseString(p_required_features).split(',').map((s) => s.trim()).filter((s) => s !== '');
		const optional_features = MeshRuntime.parseString(p_optional_features).split(',').map((s) => s.trim()).filter((s) => s !== '');
		const requested_reference_space_types = MeshRuntime.parseString(p_requested_reference_spaces).split(',').map((s) => s.trim());
		const onstarted = MeshRuntime.get_func(p_on_session_started);
		const onended = MeshRuntime.get_func(p_on_session_ended);
		const onfailed = MeshRuntime.get_func(p_on_session_failed);
		const oncontroller = MeshRuntime.get_func(p_on_controller_changed);
		const oninputevent = MeshRuntime.get_func(p_on_input_event);
		const onsimpleevent = MeshRuntime.get_func(p_on_simple_event);

		const session_init = {};
		if (required_features.length > 0) {
			session_init['requiredFeatures'] = required_features;
		}
		if (optional_features.length > 0) {
			session_init['optionalFeatures'] = optional_features;
		}

		navigator.xr.requestSession(session_mode, session_init).then(function (session) {
			MeshWebXR.session = session;

			session.addEventListener('end', function (evt) {
				onended();
			});

			session.addEventListener('inputsourceschange', function (evt) {
				let controller_changed = false;
				[evt.added, evt.removed].forEach((lst) => {
					lst.forEach((input_source) => {
						if (input_source.targetRayMode === 'tracked-pointer') {
							controller_changed = true;
						}
					});
				});
				if (controller_changed) {
					oncontroller();
				}
			});

			['selectstart', 'select', 'selectend', 'squeezestart', 'squeeze', 'squeezeend'].forEach((input_event) => {
				session.addEventListener(input_event, function (evt) {
					const c_str = MeshRuntime.allocString(input_event);
					oninputevent(c_str, MeshWebXR.getControllerId(evt.inputSource));
					MeshRuntime.free(c_str);
				});
			});

			session.addEventListener('visibilitychange', function (evt) {
				const c_str = MeshRuntime.allocString('visibility_state_changed');
				onsimpleevent(c_str);
				MeshRuntime.free(c_str);
			});

			const gl_context_handle = _emscripten_webgl_get_current_context(); // eslint-disable-line no-undef
			const gl = GL.getContext(gl_context_handle).GLctx;
			MeshWebXR.gl = gl;

			gl.makeXRCompatible().then(function () {
				session.updateRenderState({
					baseLayer: new XRWebGLLayer(session, gl),
				});

				function onReferenceSpaceSuccess(reference_space, reference_space_type) {
					MeshWebXR.space = reference_space;

					// Using reference_space.addEventListener() crashes when
					// using the polyfill with the WebXR Emulator extension,
					// so we set the event property instead.
					reference_space.onreset = function (evt) {
						const c_str = MeshRuntime.allocString('reference_space_reset');
						onsimpleevent(c_str);
						MeshRuntime.free(c_str);
					};

					// Now that both MeshWebXR.session and MeshWebXR.space are
					// set, we need to pause and resume the main loop for the XR
					// main loop to kick in.
					MeshWebXR.pauseResumeMainLoop();

					// Call in setTimeout() so that errors in the onstarted()
					// callback don't bubble up here and cause Mesh to try the
					// next reference space.
					window.setTimeout(function () {
						const c_str = MeshRuntime.allocString(reference_space_type);
						onstarted(c_str);
						MeshRuntime.free(c_str);
					}, 0);
				}

				function requestReferenceSpace() {
					const reference_space_type = requested_reference_space_types.shift();
					session.requestReferenceSpace(reference_space_type)
						.then((refSpace) => {
							onReferenceSpaceSuccess(refSpace, reference_space_type);
						})
						.catch(() => {
							if (requested_reference_space_types.length === 0) {
								const c_str = MeshRuntime.allocString('Unable to get any of the requested reference space types');
								onfailed(c_str);
								MeshRuntime.free(c_str);
							} else {
								requestReferenceSpace();
							}
						});
				}

				requestReferenceSpace();
			}).catch(function (error) {
				const c_str = MeshRuntime.allocString(`Unable to make WebGL context compatible with WebXR: ${error}`);
				onfailed(c_str);
				MeshRuntime.free(c_str);
			});
		}).catch(function (error) {
			const c_str = MeshRuntime.allocString(`Unable to start session: ${error}`);
			onfailed(c_str);
			MeshRuntime.free(c_str);
		});
	},

	mesh_webxr_uninitialize__proxy: 'sync',
	mesh_webxr_uninitialize__sig: 'v',
	mesh_webxr_uninitialize: function () {
		if (MeshWebXR.session) {
			MeshWebXR.session.end()
				// Prevent exception when session has already ended.
				.catch((e) => { });
		}

		// Clean-up the textures we allocated for each view.
		const gl = MeshWebXR.gl;
		for (let i = 0; i < MeshWebXR.textures.length; i++) {
			const texture = MeshWebXR.textures[i];
			if (texture !== null) {
				gl.deleteTexture(texture);
			}
			MeshWebXR.textures[i] = null;

			const texture_id = MeshWebXR.texture_ids[i];
			if (texture_id !== null) {
				GL.textures[texture_id] = null;
			}
			MeshWebXR.texture_ids[i] = null;
		}

		MeshWebXR.session = null;
		MeshWebXR.space = null;
		MeshWebXR.frame = null;
		MeshWebXR.pose = null;

		// Disable the monkey-patched window.requestAnimationFrame() and
		// pause/restart the main loop to activate it on all platforms.
		MeshWebXR.monkeyPatchRequestAnimationFrame(false);
		MeshWebXR.pauseResumeMainLoop();
	},

	mesh_webxr_get_view_count__proxy: 'sync',
	mesh_webxr_get_view_count__sig: 'i',
	mesh_webxr_get_view_count: function () {
		if (!MeshWebXR.session || !MeshWebXR.pose) {
			return 0;
		}
		return MeshWebXR.pose.views.length;
	},

	mesh_webxr_get_render_target_size__proxy: 'sync',
	mesh_webxr_get_render_target_size__sig: 'i',
	mesh_webxr_get_render_target_size: function () {
		if (!MeshWebXR.session || !MeshWebXR.pose) {
			return 0;
		}

		const glLayer = MeshWebXR.session.renderState.baseLayer;
		const view = MeshWebXR.pose.views[0];
		const viewport = glLayer.getViewport(view);

		const buf = MeshRuntime.malloc(2 * 4);
		MeshRuntime.setHeapValue(buf + 0, viewport.width, 'i32');
		MeshRuntime.setHeapValue(buf + 4, viewport.height, 'i32');
		return buf;
	},

	mesh_webxr_get_transform_for_eye__proxy: 'sync',
	mesh_webxr_get_transform_for_eye__sig: 'ii',
	mesh_webxr_get_transform_for_eye: function (p_eye) {
		if (!MeshWebXR.session || !MeshWebXR.pose) {
			return 0;
		}

		const views = MeshWebXR.pose.views;
		let matrix;
		if (p_eye === 0) {
			matrix = MeshWebXR.pose.transform.matrix;
		} else {
			matrix = views[p_eye - 1].transform.matrix;
		}
		const buf = MeshRuntime.malloc(16 * 4);
		for (let i = 0; i < 16; i++) {
			MeshRuntime.setHeapValue(buf + (i * 4), matrix[i], 'float');
		}
		return buf;
	},

	mesh_webxr_get_projection_for_eye__proxy: 'sync',
	mesh_webxr_get_projection_for_eye__sig: 'ii',
	mesh_webxr_get_projection_for_eye: function (p_eye) {
		if (!MeshWebXR.session || !MeshWebXR.pose) {
			return 0;
		}

		const view_index = (p_eye === 2 /* ARVRInterface::EYE_RIGHT */) ? 1 : 0;
		const matrix = MeshWebXR.pose.views[view_index].projectionMatrix;
		const buf = MeshRuntime.malloc(16 * 4);
		for (let i = 0; i < 16; i++) {
			MeshRuntime.setHeapValue(buf + (i * 4), matrix[i], 'float');
		}
		return buf;
	},

	mesh_webxr_get_external_texture_for_eye__proxy: 'sync',
	mesh_webxr_get_external_texture_for_eye__sig: 'ii',
	mesh_webxr_get_external_texture_for_eye: function (p_eye) {
		if (!MeshWebXR.session) {
			return 0;
		}

		const view_index = (p_eye === 2 /* ARVRInterface::EYE_RIGHT */) ? 1 : 0;
		if (MeshWebXR.texture_ids[view_index]) {
			return MeshWebXR.texture_ids[view_index];
		}

		// Check pose separately and after returning the cached texture id,
		// because we won't get a pose in some cases if we lose tracking, and
		// we don't want to return 0 just because tracking was lost.
		if (!MeshWebXR.pose) {
			return 0;
		}

		const glLayer = MeshWebXR.session.renderState.baseLayer;
		const view = MeshWebXR.pose.views[view_index];
		const viewport = glLayer.getViewport(view);
		const gl = MeshWebXR.gl;

		const texture = gl.createTexture();
		gl.bindTexture(gl.TEXTURE_2D, texture);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, viewport.width, viewport.height, 0, gl.RGBA, gl.UNSIGNED_BYTE, null);

		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.bindTexture(gl.TEXTURE_2D, null);

		const texture_id = GL.getNewId(GL.textures);
		GL.textures[texture_id] = texture;
		MeshWebXR.textures[view_index] = texture;
		MeshWebXR.texture_ids[view_index] = texture_id;
		return texture_id;
	},

	mesh_webxr_commit_for_eye__proxy: 'sync',
	mesh_webxr_commit_for_eye__sig: 'vi',
	mesh_webxr_commit_for_eye: function (p_eye) {
		if (!MeshWebXR.session || !MeshWebXR.pose) {
			return;
		}

		const view_index = (p_eye === 2 /* ARVRInterface::EYE_RIGHT */) ? 1 : 0;
		const glLayer = MeshWebXR.session.renderState.baseLayer;
		const view = MeshWebXR.pose.views[view_index];
		const viewport = glLayer.getViewport(view);
		const gl = MeshWebXR.gl;

		const orig_framebuffer = gl.getParameter(gl.FRAMEBUFFER_BINDING);
		const orig_viewport = gl.getParameter(gl.VIEWPORT);

		// Bind to WebXR's framebuffer.
		gl.bindFramebuffer(gl.FRAMEBUFFER, glLayer.framebuffer);
		gl.viewport(viewport.x, viewport.y, viewport.width, viewport.height);

		MeshWebXR.blitTexture(gl, MeshWebXR.textures[view_index]);

		// Restore state.
		gl.bindFramebuffer(gl.FRAMEBUFFER, orig_framebuffer);
		gl.viewport(orig_viewport[0], orig_viewport[1], orig_viewport[2], orig_viewport[3]);
	},

	mesh_webxr_sample_controller_data__proxy: 'sync',
	mesh_webxr_sample_controller_data__sig: 'v',
	mesh_webxr_sample_controller_data: function () {
		MeshWebXR.sampleControllers();
	},

	mesh_webxr_get_controller_count__proxy: 'sync',
	mesh_webxr_get_controller_count__sig: 'i',
	mesh_webxr_get_controller_count: function () {
		if (!MeshWebXR.session || !MeshWebXR.frame) {
			return 0;
		}
		return MeshWebXR.controllers.length;
	},

	mesh_webxr_is_controller_connected__proxy: 'sync',
	mesh_webxr_is_controller_connected__sig: 'ii',
	mesh_webxr_is_controller_connected: function (p_controller) {
		if (!MeshWebXR.session || !MeshWebXR.frame) {
			return false;
		}
		return !!MeshWebXR.controllers[p_controller];
	},

	mesh_webxr_get_controller_transform__proxy: 'sync',
	mesh_webxr_get_controller_transform__sig: 'ii',
	mesh_webxr_get_controller_transform: function (p_controller) {
		if (!MeshWebXR.session || !MeshWebXR.frame) {
			return 0;
		}

		const controller = MeshWebXR.controllers[p_controller];
		if (!controller) {
			return 0;
		}

		const frame = MeshWebXR.frame;
		const space = MeshWebXR.space;

		const pose = frame.getPose(controller.targetRaySpace, space);
		if (!pose) {
			// This can mean that the controller lost tracking.
			return 0;
		}
		const matrix = pose.transform.matrix;

		const buf = MeshRuntime.malloc(16 * 4);
		for (let i = 0; i < 16; i++) {
			MeshRuntime.setHeapValue(buf + (i * 4), matrix[i], 'float');
		}
		return buf;
	},

	mesh_webxr_get_controller_buttons__proxy: 'sync',
	mesh_webxr_get_controller_buttons__sig: 'ii',
	mesh_webxr_get_controller_buttons: function (p_controller) {
		if (MeshWebXR.controllers.length === 0) {
			return 0;
		}

		const controller = MeshWebXR.controllers[p_controller];
		if (!controller || !controller.gamepad) {
			return 0;
		}

		const button_count = controller.gamepad.buttons.length;

		const buf = MeshRuntime.malloc((button_count + 1) * 4);
		MeshRuntime.setHeapValue(buf, button_count, 'i32');
		for (let i = 0; i < button_count; i++) {
			MeshRuntime.setHeapValue(buf + 4 + (i * 4), controller.gamepad.buttons[i].value, 'float');
		}
		return buf;
	},

	mesh_webxr_get_controller_axes__proxy: 'sync',
	mesh_webxr_get_controller_axes__sig: 'ii',
	mesh_webxr_get_controller_axes: function (p_controller) {
		if (MeshWebXR.controllers.length === 0) {
			return 0;
		}

		const controller = MeshWebXR.controllers[p_controller];
		if (!controller || !controller.gamepad) {
			return 0;
		}

		const axes_count = controller.gamepad.axes.length;

		const buf = MeshRuntime.malloc((axes_count + 1) * 4);
		MeshRuntime.setHeapValue(buf, axes_count, 'i32');
		for (let i = 0; i < axes_count; i++) {
			let value = controller.gamepad.axes[i];
			if (i === 1 || i === 3) {
				// Invert the Y-axis on thumbsticks and trackpads, in order to
				// match OpenXR and other XR platform SDKs.
				value *= -1.0;
			}
			MeshRuntime.setHeapValue(buf + 4 + (i * 4), value, 'float');
		}
		return buf;
	},

	mesh_webxr_get_visibility_state__proxy: 'sync',
	mesh_webxr_get_visibility_state__sig: 'i',
	mesh_webxr_get_visibility_state: function () {
		if (!MeshWebXR.session || !MeshWebXR.session.visibilityState) {
			return 0;
		}

		return MeshRuntime.allocString(MeshWebXR.session.visibilityState);
	},

	mesh_webxr_get_bounds_geometry__proxy: 'sync',
	mesh_webxr_get_bounds_geometry__sig: 'i',
	mesh_webxr_get_bounds_geometry: function () {
		if (!MeshWebXR.space || !MeshWebXR.space.boundsGeometry) {
			return 0;
		}

		const point_count = MeshWebXR.space.boundsGeometry.length;
		if (point_count === 0) {
			return 0;
		}

		const buf = MeshRuntime.malloc(((point_count * 3) + 1) * 4);
		MeshRuntime.setHeapValue(buf, point_count, 'i32');
		for (let i = 0; i < point_count; i++) {
			const point = MeshWebXR.space.boundsGeometry[i];
			MeshRuntime.setHeapValue(buf + ((i * 3) + 1) * 4, point.x, 'float');
			MeshRuntime.setHeapValue(buf + ((i * 3) + 2) * 4, point.y, 'float');
			MeshRuntime.setHeapValue(buf + ((i * 3) + 3) * 4, point.z, 'float');
		}

		return buf;
	},
};

autoAddDeps(MeshWebXR, '$MeshWebXR');
mergeInto(LibraryManager.library, MeshWebXR);
