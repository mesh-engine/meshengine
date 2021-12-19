/*************************************************************************/
/*  mesh_webxr.h                                                        */
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

#ifndef MESH_WEBXR_H
#define MESH_WEBXR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

typedef void (*MeshWebXRSupportedCallback)(char *p_session_mode, int p_supported);
typedef void (*MeshWebXRStartedCallback)(char *p_reference_space_type);
typedef void (*MeshWebXREndedCallback)();
typedef void (*MeshWebXRFailedCallback)(char *p_message);
typedef void (*MeshWebXRControllerCallback)();
typedef void (*MeshWebXRInputEventCallback)(char *p_signal_name, int p_controller_id);
typedef void (*MeshWebXRSimpleEventCallback)(char *p_signal_name);

extern int mesh_webxr_is_supported();
extern void mesh_webxr_is_session_supported(const char *p_session_mode, MeshWebXRSupportedCallback p_callback);

extern void mesh_webxr_initialize(
		const char *p_session_mode,
		const char *p_required_features,
		const char *p_optional_features,
		const char *p_requested_reference_space_types,
		MeshWebXRStartedCallback p_on_session_started,
		MeshWebXREndedCallback p_on_session_ended,
		MeshWebXRFailedCallback p_on_session_failed,
		MeshWebXRControllerCallback p_on_controller_changed,
		MeshWebXRInputEventCallback p_on_input_event,
		MeshWebXRSimpleEventCallback p_on_simple_event);
extern void mesh_webxr_uninitialize();

extern int mesh_webxr_get_view_count();
extern int *mesh_webxr_get_render_target_size();
extern float *mesh_webxr_get_transform_for_eye(int p_eye);
extern float *mesh_webxr_get_projection_for_eye(int p_eye);
extern int mesh_webxr_get_external_texture_for_eye(int p_eye);
extern void mesh_webxr_commit_for_eye(int p_eye);

extern void mesh_webxr_sample_controller_data();
extern int mesh_webxr_get_controller_count();
extern int mesh_webxr_is_controller_connected(int p_controller);
extern float *mesh_webxr_get_controller_transform(int p_controller);
extern int *mesh_webxr_get_controller_buttons(int p_controller);
extern int *mesh_webxr_get_controller_axes(int p_controller);

extern char *mesh_webxr_get_visibility_state();
extern int *mesh_webxr_get_bounds_geometry();

#ifdef __cplusplus
}
#endif

#endif /* MESH_WEBXR_H */
