/*************************************************************************/
/*  mesh_audio.h                                                        */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           MESH ENGINE                                */
/*                      https://mesh-engine.com                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
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

#ifndef MESH_AUDIO_H
#define MESH_AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

extern int mesh_audio_is_available();
extern int mesh_audio_has_worklet();
extern int mesh_audio_has_script_processor();
extern int mesh_audio_init(int *p_mix_rate, int p_latency, void (*_state_cb)(int), void (*_latency_cb)(float));
extern void mesh_audio_resume();

extern int mesh_audio_capture_start();
extern void mesh_audio_capture_stop();

// Worklet
typedef int32_t GodotAudioState[4];
extern int mesh_audio_worklet_create(int p_channels);
extern void mesh_audio_worklet_start(float *p_in_buf, int p_in_size, float *p_out_buf, int p_out_size, GodotAudioState p_state);
extern void mesh_audio_worklet_start_no_threads(float *p_out_buf, int p_out_size, void (*p_out_cb)(int p_pos, int p_frames), float *p_in_buf, int p_in_size, void (*p_in_cb)(int p_pos, int p_frames));
extern int mesh_audio_worklet_state_add(GodotAudioState p_state, int p_idx, int p_value);
extern int mesh_audio_worklet_state_get(GodotAudioState p_state, int p_idx);
extern int mesh_audio_worklet_state_wait(int32_t *p_state, int p_idx, int32_t p_expected, int p_timeout);

// Script
extern int mesh_audio_script_create(int *p_buffer_size, int p_channels);
extern void mesh_audio_script_start(float *p_in_buf, int p_in_size, float *p_out_buf, int p_out_size, void (*p_cb)());

#ifdef __cplusplus
}
#endif

#endif /* MESH_AUDIO_H */
