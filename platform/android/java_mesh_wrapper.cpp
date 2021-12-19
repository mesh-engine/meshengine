/*************************************************************************/
/*  java_mesh_wrapper.cpp                                               */
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

#include "java_mesh_wrapper.h"

// JNIEnv is only valid within the thread it belongs to, in a multi threading environment
// we can't cache it.
// For Mesh we call most access methods from our thread and we thus get a valid JNIEnv
// from get_jni_env(). For one or two we expect to pass the environment

// TODO we could probably create a base class for this...

MeshJavaWrapper::MeshJavaWrapper(JNIEnv *p_env, jobject p_activity, jobject p_mesh_instance) {
	mesh_instance = p_env->NewGlobalRef(p_mesh_instance);
	activity = p_env->NewGlobalRef(p_activity);

	// get info about our Mesh class so we can get pointers and stuff...
	mesh_class = p_env->FindClass("org/meshengine/mesh/Mesh");
	if (mesh_class) {
		mesh_class = (jclass)p_env->NewGlobalRef(mesh_class);
	} else {
		// this is a pretty serious fail.. bail... pointers will stay 0
		return;
	}
	activity_class = p_env->FindClass("android/app/Activity");
	if (activity_class) {
		activity_class = (jclass)p_env->NewGlobalRef(activity_class);
	} else {
		// this is a pretty serious fail.. bail... pointers will stay 0
		return;
	}

	// get some Mesh method pointers...
	_on_video_init = p_env->GetMethodID(mesh_class, "onVideoInit", "()V");
	_restart = p_env->GetMethodID(mesh_class, "restart", "()V");
	_finish = p_env->GetMethodID(mesh_class, "forceQuit", "()V");
	_set_keep_screen_on = p_env->GetMethodID(mesh_class, "setKeepScreenOn", "(Z)V");
	_alert = p_env->GetMethodID(mesh_class, "alert", "(Ljava/lang/String;Ljava/lang/String;)V");
	_get_GLES_version_code = p_env->GetMethodID(mesh_class, "getGLESVersionCode", "()I");
	_get_clipboard = p_env->GetMethodID(mesh_class, "getClipboard", "()Ljava/lang/String;");
	_set_clipboard = p_env->GetMethodID(mesh_class, "setClipboard", "(Ljava/lang/String;)V");
	_request_permission = p_env->GetMethodID(mesh_class, "requestPermission", "(Ljava/lang/String;)Z");
	_request_permissions = p_env->GetMethodID(mesh_class, "requestPermissions", "()Z");
	_get_granted_permissions = p_env->GetMethodID(mesh_class, "getGrantedPermissions", "()[Ljava/lang/String;");
	_init_input_devices = p_env->GetMethodID(mesh_class, "initInputDevices", "()V");
	_get_surface = p_env->GetMethodID(mesh_class, "getSurface", "()Landroid/view/Surface;");
	_is_activity_resumed = p_env->GetMethodID(mesh_class, "isActivityResumed", "()Z");
	_vibrate = p_env->GetMethodID(mesh_class, "vibrate", "(I)V");
	_get_input_fallback_mapping = p_env->GetMethodID(mesh_class, "getInputFallbackMapping", "()Ljava/lang/String;");
	_on_mesh_setup_completed = p_env->GetMethodID(mesh_class, "onMeshSetupCompleted", "()V");
	_on_mesh_main_loop_started = p_env->GetMethodID(mesh_class, "onMeshMainLoopStarted", "()V");

	// get some Activity method pointers...
	_get_class_loader = p_env->GetMethodID(activity_class, "getClassLoader", "()Ljava/lang/ClassLoader;");
}

MeshJavaWrapper::~MeshJavaWrapper() {
	// nothing to do here for now
}

jobject MeshJavaWrapper::get_activity() {
	return activity;
}

jobject MeshJavaWrapper::get_member_object(const char *p_name, const char *p_class, JNIEnv *p_env) {
	if (mesh_class) {
		if (p_env == nullptr)
			p_env = get_jni_env();

		ERR_FAIL_COND_V(p_env == nullptr, nullptr);

		jfieldID fid = p_env->GetStaticFieldID(mesh_class, p_name, p_class);
		return p_env->GetStaticObjectField(mesh_class, fid);
	} else {
		return nullptr;
	}
}

jobject MeshJavaWrapper::get_class_loader() {
	if (_get_class_loader) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, nullptr);

		return env->CallObjectMethod(activity, _get_class_loader);
	} else {
		return nullptr;
	}
}

MeshJavaViewWrapper *MeshJavaWrapper::get_mesh_view() {
	if (_mesh_view != nullptr) {
		return _mesh_view;
	}
	JNIEnv *env = get_jni_env();
	ERR_FAIL_COND_V(env == nullptr, nullptr);

	jmethodID mesh_view_getter = env->GetMethodID(mesh_class, "getRenderView", "()Lorg/meshengine/mesh/MeshRenderView;");
	_mesh_view = new MeshJavaViewWrapper(env->CallObjectMethod(mesh_instance, mesh_view_getter));
	return _mesh_view;
}

void MeshJavaWrapper::on_video_init(JNIEnv *p_env) {
	if (_on_video_init) {
		if (p_env == nullptr)
			p_env = get_jni_env();
		ERR_FAIL_COND(p_env == nullptr);

		p_env->CallVoidMethod(mesh_instance, _on_video_init);
	}
}

void MeshJavaWrapper::on_mesh_setup_completed(JNIEnv *p_env) {
	if (_on_mesh_setup_completed) {
		if (p_env == nullptr) {
			p_env = get_jni_env();
		}
		p_env->CallVoidMethod(mesh_instance, _on_mesh_setup_completed);
	}
}

void MeshJavaWrapper::on_mesh_main_loop_started(JNIEnv *p_env) {
	if (_on_mesh_main_loop_started) {
		if (p_env == nullptr) {
			p_env = get_jni_env();
		}
		ERR_FAIL_COND(p_env == nullptr);
		p_env->CallVoidMethod(mesh_instance, _on_mesh_main_loop_started);
	}
}

void MeshJavaWrapper::restart(JNIEnv *p_env) {
	if (_restart) {
		if (p_env == nullptr)
			p_env = get_jni_env();
		ERR_FAIL_COND(p_env == nullptr);

		p_env->CallVoidMethod(mesh_instance, _restart);
	}
}

void MeshJavaWrapper::force_quit(JNIEnv *p_env) {
	if (_finish) {
		if (p_env == nullptr)
			p_env = get_jni_env();
		ERR_FAIL_COND(p_env == nullptr);

		p_env->CallVoidMethod(mesh_instance, _finish);
	}
}

void MeshJavaWrapper::set_keep_screen_on(bool p_enabled) {
	if (_set_keep_screen_on) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND(env == nullptr);

		env->CallVoidMethod(mesh_instance, _set_keep_screen_on, p_enabled);
	}
}

void MeshJavaWrapper::alert(const String &p_message, const String &p_title) {
	if (_alert) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND(env == nullptr);

		jstring jStrMessage = env->NewStringUTF(p_message.utf8().get_data());
		jstring jStrTitle = env->NewStringUTF(p_title.utf8().get_data());
		env->CallVoidMethod(mesh_instance, _alert, jStrMessage, jStrTitle);
	}
}

int MeshJavaWrapper::get_gles_version_code() {
	JNIEnv *env = get_jni_env();
	ERR_FAIL_COND_V(env == nullptr, 0);

	if (_get_GLES_version_code) {
		return env->CallIntMethod(mesh_instance, _get_GLES_version_code);
	}

	return 0;
}

bool MeshJavaWrapper::has_get_clipboard() {
	return _get_clipboard != 0;
}

String MeshJavaWrapper::get_clipboard() {
	if (_get_clipboard) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, String());

		jstring s = (jstring)env->CallObjectMethod(mesh_instance, _get_clipboard);
		return jstring_to_string(s, env);
	} else {
		return String();
	}
}

String MeshJavaWrapper::get_input_fallback_mapping() {
	if (_get_input_fallback_mapping) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, String());

		jstring fallback_mapping = (jstring)env->CallObjectMethod(mesh_instance, _get_input_fallback_mapping);
		return jstring_to_string(fallback_mapping, env);
	} else {
		return String();
	}
}

bool MeshJavaWrapper::has_set_clipboard() {
	return _set_clipboard != 0;
}

void MeshJavaWrapper::set_clipboard(const String &p_text) {
	if (_set_clipboard) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND(env == nullptr);

		jstring jStr = env->NewStringUTF(p_text.utf8().get_data());
		env->CallVoidMethod(mesh_instance, _set_clipboard, jStr);
	}
}

bool MeshJavaWrapper::request_permission(const String &p_name) {
	if (_request_permission) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, false);

		jstring jStrName = env->NewStringUTF(p_name.utf8().get_data());
		return env->CallBooleanMethod(mesh_instance, _request_permission, jStrName);
	} else {
		return false;
	}
}

bool MeshJavaWrapper::request_permissions() {
	if (_request_permissions) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, false);

		return env->CallBooleanMethod(mesh_instance, _request_permissions);
	} else {
		return false;
	}
}

Vector<String> MeshJavaWrapper::get_granted_permissions() const {
	Vector<String> permissions_list;
	if (_get_granted_permissions) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, permissions_list);

		jobject permissions_object = env->CallObjectMethod(mesh_instance, _get_granted_permissions);
		jobjectArray *arr = reinterpret_cast<jobjectArray *>(&permissions_object);

		int i = 0;
		jsize len = env->GetArrayLength(*arr);
		for (i = 0; i < len; i++) {
			jstring jstr = (jstring)env->GetObjectArrayElement(*arr, i);
			String str = jstring_to_string(jstr, env);
			permissions_list.push_back(str);
			env->DeleteLocalRef(jstr);
		}
	}
	return permissions_list;
}

void MeshJavaWrapper::init_input_devices() {
	if (_init_input_devices) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND(env == nullptr);

		env->CallVoidMethod(mesh_instance, _init_input_devices);
	}
}

jobject MeshJavaWrapper::get_surface() {
	if (_get_surface) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, nullptr);

		return env->CallObjectMethod(mesh_instance, _get_surface);
	} else {
		return nullptr;
	}
}

bool MeshJavaWrapper::is_activity_resumed() {
	if (_is_activity_resumed) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND_V(env == nullptr, false);

		return env->CallBooleanMethod(mesh_instance, _is_activity_resumed);
	} else {
		return false;
	}
}

void MeshJavaWrapper::vibrate(int p_duration_ms) {
	if (_vibrate) {
		JNIEnv *env = get_jni_env();
		ERR_FAIL_COND(env == nullptr);

		env->CallVoidMethod(mesh_instance, _vibrate, p_duration_ms);
	}
}
