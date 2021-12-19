/*************************************************************************/
/*  mesh_plugin_jni.h                                                   */
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

#ifndef MESH_PLUGIN_JNI_H
#define MESH_PLUGIN_JNI_H

#include <android/log.h>
#include <jni.h>

extern "C" {
JNIEXPORT void JNICALL Java_org_meshengine_mesh_plugin_MeshPlugin_nativeRegisterSingleton(JNIEnv *env, jclass clazz, jstring name, jobject obj);
JNIEXPORT void JNICALL Java_org_meshengine_mesh_plugin_MeshPlugin_nativeRegisterMethod(JNIEnv *env, jclass clazz, jstring sname, jstring name, jstring ret, jobjectArray args);
JNIEXPORT void JNICALL Java_org_meshengine_mesh_plugin_MeshPlugin_nativeRegisterSignal(JNIEnv *env, jclass clazz, jstring j_plugin_name, jstring j_signal_name, jobjectArray j_signal_param_types);
JNIEXPORT void JNICALL Java_org_meshengine_mesh_plugin_MeshPlugin_nativeEmitSignal(JNIEnv *env, jclass clazz, jstring j_plugin_name, jstring j_signal_name, jobjectArray j_signal_params);
JNIEXPORT void JNICALL Java_org_meshengine_mesh_plugin_MeshPlugin_nativeRegisterGDNativeLibraries(JNIEnv *env, jclass clazz, jobjectArray gdnlib_paths);
}

#endif // MESH_PLUGIN_JNI_H
