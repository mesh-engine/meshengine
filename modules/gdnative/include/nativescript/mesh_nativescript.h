/*************************************************************************/
/*  mesh_nativescript.h                                                 */
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

#ifndef MESH_NATIVESCRIPT_H
#define MESH_NATIVESCRIPT_H

#include <gdnative/gdnative.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	MESH_METHOD_RPC_MODE_DISABLED,
	MESH_METHOD_RPC_MODE_ANY_PEER,
	MESH_METHOD_RPC_MODE_AUTHORITY,
} mesh_nativescript_method_rpc_mode;

typedef enum {
	MESH_PROPERTY_HINT_NONE, ///< no hint provided.
	MESH_PROPERTY_HINT_RANGE, ///< hint_text = "min,max,step,slider; //slider is optional"
	MESH_PROPERTY_HINT_EXP_RANGE, ///< hint_text = "min,max,step", exponential edit
	MESH_PROPERTY_HINT_ENUM, ///< hint_text= "val1,val2,val3,etc"
	MESH_PROPERTY_HINT_EXP_EASING, /// exponential easing function (Math::ease)
	MESH_PROPERTY_HINT_LENGTH, ///< hint_text= "length" (as integer)
	MESH_PROPERTY_HINT_KEY_ACCEL, ///< hint_text= "length" (as integer)
	MESH_PROPERTY_HINT_FLAGS, ///< hint_text= "flag1,flag2,etc" (as bit flags)
	MESH_PROPERTY_HINT_LAYERS_2D_RENDER,
	MESH_PROPERTY_HINT_LAYERS_2D_PHYSICS,
	MESH_PROPERTY_HINT_LAYERS_2D_NAVIGATION,
	MESH_PROPERTY_HINT_LAYERS_3D_RENDER,
	MESH_PROPERTY_HINT_LAYERS_3D_PHYSICS,
	MESH_PROPERTY_HINT_LAYERS_3D_NAVIGATION,
	MESH_PROPERTY_HINT_FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
	MESH_PROPERTY_HINT_DIR, ///< a directory path must be passed
	MESH_PROPERTY_HINT_GLOBAL_FILE, ///< a file path must be passed, hint_text (optionally) is a filter "*.png,*.wav,*.doc,"
	MESH_PROPERTY_HINT_GLOBAL_DIR, ///< a directory path must be passed
	MESH_PROPERTY_HINT_RESOURCE_TYPE, ///< a resource object type
	MESH_PROPERTY_HINT_MULTILINE_TEXT, ///< used for string properties that can contain multiple lines
	MESH_PROPERTY_HINT_PLACEHOLDER_TEXT, ///< used to set a placeholder text for string properties
	MESH_PROPERTY_HINT_COLOR_NO_ALPHA, ///< used for ignoring alpha component when editing a color
	MESH_PROPERTY_HINT_IMAGE_COMPRESS_LOSSY,
	MESH_PROPERTY_HINT_IMAGE_COMPRESS_LOSSLESS,
	MESH_PROPERTY_HINT_OBJECT_ID,
	MESH_PROPERTY_HINT_TYPE_STRING, ///< a type string, the hint is the base type to choose
	MESH_PROPERTY_HINT_NODE_PATH_TO_EDITED_NODE, ///< so something else can provide this (used in scripts)
	MESH_PROPERTY_HINT_METHOD_OF_VARIANT_TYPE, ///< a method of a type
	MESH_PROPERTY_HINT_METHOD_OF_BASE_TYPE, ///< a method of a base type
	MESH_PROPERTY_HINT_METHOD_OF_INSTANCE, ///< a method of an instance
	MESH_PROPERTY_HINT_METHOD_OF_SCRIPT, ///< a method of a script & base
	MESH_PROPERTY_HINT_PROPERTY_OF_VARIANT_TYPE, ///< a property of a type
	MESH_PROPERTY_HINT_PROPERTY_OF_BASE_TYPE, ///< a property of a base type
	MESH_PROPERTY_HINT_PROPERTY_OF_INSTANCE, ///< a property of an instance
	MESH_PROPERTY_HINT_PROPERTY_OF_SCRIPT, ///< a property of a script & base
	MESH_PROPERTY_HINT_MAX,
} mesh_nativescript_property_hint;

typedef enum {
	MESH_PROPERTY_USAGE_STORAGE = 1,
	MESH_PROPERTY_USAGE_EDITOR = 2,
	MESH_PROPERTY_USAGE_NETWORK = 4,
	MESH_PROPERTY_USAGE_EDITOR_HELPER = 8,
	MESH_PROPERTY_USAGE_CHECKABLE = 16, //used for editing global variables
	MESH_PROPERTY_USAGE_CHECKED = 32, //used for editing global variables
	MESH_PROPERTY_USAGE_INTERNATIONALIZED = 64, //hint for internationalized strings
	MESH_PROPERTY_USAGE_GROUP = 128, //used for grouping props in the editor
	MESH_PROPERTY_USAGE_CATEGORY = 256,
	MESH_PROPERTY_USAGE_SUBGROUP = 512,
	MESH_PROPERTY_USAGE_NO_INSTANCE_STATE = 2048,
	MESH_PROPERTY_USAGE_RESTART_IF_CHANGED = 4096,
	MESH_PROPERTY_USAGE_SCRIPT_VARIABLE = 8192,
	MESH_PROPERTY_USAGE_STORE_IF_NULL = 16384,
	MESH_PROPERTY_USAGE_ANIMATE_AS_TRIGGER = 32768,
	MESH_PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED = 65536,

	MESH_PROPERTY_USAGE_DEFAULT = MESH_PROPERTY_USAGE_STORAGE | MESH_PROPERTY_USAGE_EDITOR | MESH_PROPERTY_USAGE_NETWORK,
	MESH_PROPERTY_USAGE_DEFAULT_INTL = MESH_PROPERTY_USAGE_STORAGE | MESH_PROPERTY_USAGE_EDITOR | MESH_PROPERTY_USAGE_NETWORK | MESH_PROPERTY_USAGE_INTERNATIONALIZED,
	MESH_PROPERTY_USAGE_NO_EDITOR = MESH_PROPERTY_USAGE_STORAGE | MESH_PROPERTY_USAGE_NETWORK,
} mesh_nativescript_property_usage_flags;

typedef struct {
	mesh_nativescript_method_rpc_mode rset_type;

	mesh_int type;
	mesh_nativescript_property_hint hint;
	mesh_string hint_string;
	mesh_nativescript_property_usage_flags usage;
	mesh_variant default_value;
} mesh_nativescript_property_attributes;

typedef struct {
	// instance pointer, method_data - return user data
	GDCALLINGCONV void *(*create_func)(mesh_object *, void *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} mesh_nativescript_instance_create_func;

typedef struct {
	// instance pointer, method data, user data
	GDCALLINGCONV void (*destroy_func)(mesh_object *, void *, void *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} mesh_nativescript_instance_destroy_func;

void GDAPI mesh_nativescript_register_class(void *p_gdnative_handle, const char *p_name, const char *p_base, mesh_nativescript_instance_create_func p_create_func, mesh_nativescript_instance_destroy_func p_destroy_func);

void GDAPI mesh_nativescript_register_tool_class(void *p_gdnative_handle, const char *p_name, const char *p_base, mesh_nativescript_instance_create_func p_create_func, mesh_nativescript_instance_destroy_func p_destroy_func);

typedef struct {
	mesh_nativescript_method_rpc_mode rpc_type;
} mesh_nativescript_method_attributes;

typedef struct {
	mesh_string name;

	mesh_variant_type type;
	mesh_nativescript_property_hint hint;
	mesh_string hint_string;
} mesh_nativescript_method_argument;

typedef struct {
	// instance pointer, method data, user data, num args, args - return result as varaint
	GDCALLINGCONV mesh_variant (*method)(mesh_object *, void *, void *, int, mesh_variant **);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} mesh_nativescript_instance_method;

void GDAPI mesh_nativescript_register_method(void *p_gdnative_handle, const char *p_name, const char *p_function_name, mesh_nativescript_method_attributes p_attr, mesh_nativescript_instance_method p_method);
void GDAPI mesh_nativescript_set_method_argument_information(void *p_gdnative_handle, const char *p_name, const char *p_function_name, int p_num_args, const mesh_nativescript_method_argument *p_args);

typedef struct {
	// instance pointer, method data, user data, value
	GDCALLINGCONV void (*set_func)(mesh_object *, void *, void *, mesh_variant *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} mesh_nativescript_property_set_func;

typedef struct {
	// instance pointer, method data, user data, value
	GDCALLINGCONV mesh_variant (*get_func)(mesh_object *, void *, void *);
	void *method_data;
	GDCALLINGCONV void (*free_func)(void *);
} mesh_nativescript_property_get_func;

void GDAPI mesh_nativescript_register_property(void *p_gdnative_handle, const char *p_name, const char *p_path, mesh_nativescript_property_attributes *p_attr, mesh_nativescript_property_set_func p_set_func, mesh_nativescript_property_get_func p_get_func);

typedef struct {
	mesh_string name;
	mesh_int type;
	mesh_nativescript_property_hint hint;
	mesh_string hint_string;
	mesh_nativescript_property_usage_flags usage;
	mesh_variant default_value;
} mesh_nativescript_signal_argument;

typedef struct {
	mesh_string name;
	int num_args;
	mesh_nativescript_signal_argument *args;
	int num_default_args;
	mesh_variant *default_args;
} mesh_nativescript_signal;

void GDAPI mesh_nativescript_register_signal(void *p_gdnative_handle, const char *p_name, const mesh_nativescript_signal *p_signal);

void GDAPI *mesh_nativescript_get_userdata(mesh_object *p_instance);

// documentation

void GDAPI mesh_nativescript_set_class_documentation(void *p_gdnative_handle, const char *p_name, mesh_string p_documentation);
void GDAPI mesh_nativescript_set_method_documentation(void *p_gdnative_handle, const char *p_name, const char *p_function_name, mesh_string p_documentation);
void GDAPI mesh_nativescript_set_property_documentation(void *p_gdnative_handle, const char *p_name, const char *p_path, mesh_string p_documentation);
void GDAPI mesh_nativescript_set_signal_documentation(void *p_gdnative_handle, const char *p_name, const char *p_signal_name, mesh_string p_documentation);

// type tag API

void GDAPI mesh_nativescript_set_global_type_tag(int p_idx, const char *p_name, const void *p_type_tag);
const void GDAPI *mesh_nativescript_get_global_type_tag(int p_idx, const char *p_name);

void GDAPI mesh_nativescript_set_type_tag(void *p_gdnative_handle, const char *p_name, const void *p_type_tag);
const void GDAPI *mesh_nativescript_get_type_tag(const mesh_object *p_object);

// instance binding API

typedef struct {
	GDCALLINGCONV void *(*alloc_instance_binding_data)(void *, const void *, mesh_object *);
	GDCALLINGCONV void (*free_instance_binding_data)(void *, void *);
	GDCALLINGCONV void (*refcount_incremented_instance_binding)(void *, mesh_object *);
	GDCALLINGCONV bool (*refcount_decremented_instance_binding)(void *, mesh_object *);
	void *data;
	GDCALLINGCONV void (*free_func)(void *);
} mesh_nativescript_instance_binding_functions;

int GDAPI mesh_nativescript_register_instance_binding_data_functions(mesh_nativescript_instance_binding_functions p_binding_functions);
void GDAPI mesh_nativescript_unregister_instance_binding_data_functions(int p_idx);

void GDAPI *mesh_nativescript_get_instance_binding_data(int p_idx, mesh_object *p_object);

void GDAPI mesh_nativescript_profiling_add_data(const char *p_signature, uint64_t p_time);

#ifdef __cplusplus
}
#endif

#endif
