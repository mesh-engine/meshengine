/*************************************************************************/
/*  library_mesh_webrtc.js                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           MESH ENGINE                                */
/*                      https://mesh-engine.com                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Mesh Engine contributors (cf. AUTHORS.md).   */
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

const MeshRTCDataChannel = {
	// Our socket implementation that forwards events to C++.
	$MeshRTCDataChannel__deps: ['$IDHandler', '$MeshRuntime'],
	$MeshRTCDataChannel: {
		connect: function (p_id, p_on_open, p_on_message, p_on_error, p_on_close) {
			const ref = IDHandler.get(p_id);
			if (!ref) {
				return;
			}

			ref.binaryType = 'arraybuffer';
			ref.onopen = function (event) {
				p_on_open();
			};
			ref.onclose = function (event) {
				p_on_close();
			};
			ref.onerror = function (event) {
				p_on_error();
			};
			ref.onmessage = function (event) {
				let buffer;
				let is_string = 0;
				if (event.data instanceof ArrayBuffer) {
					buffer = new Uint8Array(event.data);
				} else if (event.data instanceof Blob) {
					MeshRuntime.error('Blob type not supported');
					return;
				} else if (typeof event.data === 'string') {
					is_string = 1;
					const enc = new TextEncoder('utf-8');
					buffer = new Uint8Array(enc.encode(event.data));
				} else {
					MeshRuntime.error('Unknown message type');
					return;
				}
				const len = buffer.length * buffer.BYTES_PER_ELEMENT;
				const out = MeshRuntime.malloc(len);
				HEAPU8.set(buffer, out);
				p_on_message(out, len, is_string);
				MeshRuntime.free(out);
			};
		},

		close: function (p_id) {
			const ref = IDHandler.get(p_id);
			if (!ref) {
				return;
			}
			ref.onopen = null;
			ref.onmessage = null;
			ref.onerror = null;
			ref.onclose = null;
			ref.close();
		},

		get_prop: function (p_id, p_prop, p_def) {
			const ref = IDHandler.get(p_id);
			return (ref && ref[p_prop] !== undefined) ? ref[p_prop] : p_def;
		},
	},

	mesh_js_rtc_datachannel_ready_state_get__sig: 'ii',
	mesh_js_rtc_datachannel_ready_state_get: function (p_id) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return 3; // CLOSED
		}

		switch (ref.readyState) {
		case 'connecting':
			return 0;
		case 'open':
			return 1;
		case 'closing':
			return 2;
		case 'closed':
		default:
			return 3;
		}
	},

	mesh_js_rtc_datachannel_send__sig: 'iiiii',
	mesh_js_rtc_datachannel_send: function (p_id, p_buffer, p_length, p_raw) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return 1;
		}

		const bytes_array = new Uint8Array(p_length);
		for (let i = 0; i < p_length; i++) {
			bytes_array[i] = MeshRuntime.getHeapValue(p_buffer + i, 'i8');
		}

		if (p_raw) {
			ref.send(bytes_array.buffer);
		} else {
			const string = new TextDecoder('utf-8').decode(bytes_array);
			ref.send(string);
		}
		return 0;
	},

	mesh_js_rtc_datachannel_is_ordered__sig: 'ii',
	mesh_js_rtc_datachannel_is_ordered: function (p_id) {
		return MeshRTCDataChannel.get_prop(p_id, 'ordered', true);
	},

	mesh_js_rtc_datachannel_id_get__sig: 'ii',
	mesh_js_rtc_datachannel_id_get: function (p_id) {
		return MeshRTCDataChannel.get_prop(p_id, 'id', 65535);
	},

	mesh_js_rtc_datachannel_max_packet_lifetime_get__sig: 'ii',
	mesh_js_rtc_datachannel_max_packet_lifetime_get: function (p_id) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return 65535;
		}
		if (ref['maxPacketLifeTime'] !== undefined) {
			return ref['maxPacketLifeTime'];
		} else if (ref['maxRetransmitTime'] !== undefined) {
			// Guess someone didn't appreciate the standardization process.
			return ref['maxRetransmitTime'];
		}
		return 65535;
	},

	mesh_js_rtc_datachannel_max_retransmits_get__sig: 'ii',
	mesh_js_rtc_datachannel_max_retransmits_get: function (p_id) {
		return MeshRTCDataChannel.get_prop(p_id, 'maxRetransmits', 65535);
	},

	mesh_js_rtc_datachannel_is_negotiated__sig: 'ii',
	mesh_js_rtc_datachannel_is_negotiated: function (p_id) {
		return MeshRTCDataChannel.get_prop(p_id, 'negotiated', 65535);
	},

	mesh_js_rtc_datachannel_get_buffered_amount__sig: 'ii',
	mesh_js_rtc_datachannel_get_buffered_amount: function (p_id) {
		return MeshRTCDataChannel.get_prop(p_id, 'bufferedAmount', 0);
	},

	mesh_js_rtc_datachannel_label_get__sig: 'ii',
	mesh_js_rtc_datachannel_label_get: function (p_id) {
		const ref = IDHandler.get(p_id);
		if (!ref || !ref.label) {
			return 0;
		}
		return MeshRuntime.allocString(ref.label);
	},

	mesh_js_rtc_datachannel_protocol_get__sig: 'ii',
	mesh_js_rtc_datachannel_protocol_get: function (p_id) {
		const ref = IDHandler.get(p_id);
		if (!ref || !ref.protocol) {
			return 0;
		}
		return MeshRuntime.allocString(ref.protocol);
	},

	mesh_js_rtc_datachannel_destroy__sig: 'vi',
	mesh_js_rtc_datachannel_destroy: function (p_id) {
		MeshRTCDataChannel.close(p_id);
		IDHandler.remove(p_id);
	},

	mesh_js_rtc_datachannel_connect__sig: 'viiiiii',
	mesh_js_rtc_datachannel_connect: function (p_id, p_ref, p_on_open, p_on_message, p_on_error, p_on_close) {
		const onopen = MeshRuntime.get_func(p_on_open).bind(null, p_ref);
		const onmessage = MeshRuntime.get_func(p_on_message).bind(null, p_ref);
		const onerror = MeshRuntime.get_func(p_on_error).bind(null, p_ref);
		const onclose = MeshRuntime.get_func(p_on_close).bind(null, p_ref);
		MeshRTCDataChannel.connect(p_id, onopen, onmessage, onerror, onclose);
	},

	mesh_js_rtc_datachannel_close__sig: 'vi',
	mesh_js_rtc_datachannel_close: function (p_id) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return;
		}
		MeshRTCDataChannel.close(p_id);
	},
};

autoAddDeps(MeshRTCDataChannel, '$MeshRTCDataChannel');
mergeInto(LibraryManager.library, MeshRTCDataChannel);

const MeshRTCPeerConnection = {
	$MeshRTCPeerConnection__deps: ['$IDHandler', '$MeshRuntime', '$MeshRTCDataChannel'],
	$MeshRTCPeerConnection: {
		onstatechange: function (p_id, p_conn, callback, event) {
			const ref = IDHandler.get(p_id);
			if (!ref) {
				return;
			}
			let state;
			switch (p_conn.iceConnectionState) {
			case 'new':
				state = 0;
				break;
			case 'checking':
				state = 1;
				break;
			case 'connected':
			case 'completed':
				state = 2;
				break;
			case 'disconnected':
				state = 3;
				break;
			case 'failed':
				state = 4;
				break;
			case 'closed':
			default:
				state = 5;
				break;
			}
			callback(state);
		},

		onicecandidate: function (p_id, callback, event) {
			const ref = IDHandler.get(p_id);
			if (!ref || !event.candidate) {
				return;
			}

			const c = event.candidate;
			const candidate_str = MeshRuntime.allocString(c.candidate);
			const mid_str = MeshRuntime.allocString(c.sdpMid);
			callback(mid_str, c.sdpMLineIndex, candidate_str);
			MeshRuntime.free(candidate_str);
			MeshRuntime.free(mid_str);
		},

		ondatachannel: function (p_id, callback, event) {
			const ref = IDHandler.get(p_id);
			if (!ref) {
				return;
			}

			const cid = IDHandler.add(event.channel);
			callback(cid);
		},

		onsession: function (p_id, callback, session) {
			const ref = IDHandler.get(p_id);
			if (!ref) {
				return;
			}
			const type_str = MeshRuntime.allocString(session.type);
			const sdp_str = MeshRuntime.allocString(session.sdp);
			callback(type_str, sdp_str);
			MeshRuntime.free(type_str);
			MeshRuntime.free(sdp_str);
		},

		onerror: function (p_id, callback, error) {
			const ref = IDHandler.get(p_id);
			if (!ref) {
				return;
			}
			MeshRuntime.error(error);
			callback();
		},
	},

	mesh_js_rtc_pc_create__sig: 'iiiiii',
	mesh_js_rtc_pc_create: function (p_config, p_ref, p_on_state_change, p_on_candidate, p_on_datachannel) {
		const onstatechange = MeshRuntime.get_func(p_on_state_change).bind(null, p_ref);
		const oncandidate = MeshRuntime.get_func(p_on_candidate).bind(null, p_ref);
		const ondatachannel = MeshRuntime.get_func(p_on_datachannel).bind(null, p_ref);

		const config = JSON.parse(MeshRuntime.parseString(p_config));
		let conn = null;
		try {
			conn = new RTCPeerConnection(config);
		} catch (e) {
			MeshRuntime.error(e);
			return 0;
		}

		const base = MeshRTCPeerConnection;
		const id = IDHandler.add(conn);
		conn.oniceconnectionstatechange = base.onstatechange.bind(null, id, conn, onstatechange);
		conn.onicecandidate = base.onicecandidate.bind(null, id, oncandidate);
		conn.ondatachannel = base.ondatachannel.bind(null, id, ondatachannel);
		return id;
	},

	mesh_js_rtc_pc_close__sig: 'vi',
	mesh_js_rtc_pc_close: function (p_id) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return;
		}
		ref.close();
	},

	mesh_js_rtc_pc_destroy__sig: 'vi',
	mesh_js_rtc_pc_destroy: function (p_id) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return;
		}
		ref.oniceconnectionstatechange = null;
		ref.onicecandidate = null;
		ref.ondatachannel = null;
		IDHandler.remove(p_id);
	},

	mesh_js_rtc_pc_offer_create__sig: 'viiii',
	mesh_js_rtc_pc_offer_create: function (p_id, p_obj, p_on_session, p_on_error) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return;
		}
		const onsession = MeshRuntime.get_func(p_on_session).bind(null, p_obj);
		const onerror = MeshRuntime.get_func(p_on_error).bind(null, p_obj);
		ref.createOffer().then(function (session) {
			MeshRTCPeerConnection.onsession(p_id, onsession, session);
		}).catch(function (error) {
			MeshRTCPeerConnection.onerror(p_id, onerror, error);
		});
	},

	mesh_js_rtc_pc_local_description_set__sig: 'viiiii',
	mesh_js_rtc_pc_local_description_set: function (p_id, p_type, p_sdp, p_obj, p_on_error) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return;
		}
		const type = MeshRuntime.parseString(p_type);
		const sdp = MeshRuntime.parseString(p_sdp);
		const onerror = MeshRuntime.get_func(p_on_error).bind(null, p_obj);
		ref.setLocalDescription({
			'sdp': sdp,
			'type': type,
		}).catch(function (error) {
			MeshRTCPeerConnection.onerror(p_id, onerror, error);
		});
	},

	mesh_js_rtc_pc_remote_description_set__sig: 'viiiiii',
	mesh_js_rtc_pc_remote_description_set: function (p_id, p_type, p_sdp, p_obj, p_session_created, p_on_error) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return;
		}
		const type = MeshRuntime.parseString(p_type);
		const sdp = MeshRuntime.parseString(p_sdp);
		const onerror = MeshRuntime.get_func(p_on_error).bind(null, p_obj);
		const onsession = MeshRuntime.get_func(p_session_created).bind(null, p_obj);
		ref.setRemoteDescription({
			'sdp': sdp,
			'type': type,
		}).then(function () {
			if (type !== 'offer') {
				return Promise.resolve();
			}
			return ref.createAnswer().then(function (session) {
				MeshRTCPeerConnection.onsession(p_id, onsession, session);
			});
		}).catch(function (error) {
			MeshRTCPeerConnection.onerror(p_id, onerror, error);
		});
	},

	mesh_js_rtc_pc_ice_candidate_add__sig: 'viiii',
	mesh_js_rtc_pc_ice_candidate_add: function (p_id, p_mid_name, p_mline_idx, p_sdp) {
		const ref = IDHandler.get(p_id);
		if (!ref) {
			return;
		}
		const sdpMidName = MeshRuntime.parseString(p_mid_name);
		const sdpName = MeshRuntime.parseString(p_sdp);
		ref.addIceCandidate(new RTCIceCandidate({
			'candidate': sdpName,
			'sdpMid': sdpMidName,
			'sdpMlineIndex': p_mline_idx,
		}));
	},

	mesh_js_rtc_pc_datachannel_create__deps: ['$MeshRTCDataChannel'],
	mesh_js_rtc_pc_datachannel_create__sig: 'iiii',
	mesh_js_rtc_pc_datachannel_create: function (p_id, p_label, p_config) {
		try {
			const ref = IDHandler.get(p_id);
			if (!ref) {
				return 0;
			}

			const label = MeshRuntime.parseString(p_label);
			const config = JSON.parse(MeshRuntime.parseString(p_config));

			const channel = ref.createDataChannel(label, config);
			return IDHandler.add(channel);
		} catch (e) {
			MeshRuntime.error(e);
			return 0;
		}
	},
};

autoAddDeps(MeshRTCPeerConnection, '$MeshRTCPeerConnection');
mergeInto(LibraryManager.library, MeshRTCPeerConnection);
