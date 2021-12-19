/*************************************************************************/
/*  mesh_pluginscript.h                                                 */
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

#ifndef MESH_PLUGINSCRIPT_H
#define MESH_PLUGINSCRIPT_H

#include <gdnative/gdnative.h>
#include <nativescript/mesh_nativescript.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void mesh_pluginscript_instance_data;
typedef void mesh_pluginscript_script_data;
typedef void mesh_pluginscript_language_data;

// --- Instance ---

typedef struct {
	mesh_pluginscript_instance_data *(*init)(mesh_pluginscript_script_data *p_data, mesh_object *p_owner);
	void (*finish)(mesh_pluginscript_instance_data *p_data);

	mesh_bool (*set_prop)(mesh_pluginscript_instance_data *p_data, const mesh_string_name *p_name, const mesh_variant *p_value);
	mesh_bool (*get_prop)(mesh_pluginscript_instance_data *p_data, const mesh_string_name *p_name, mesh_variant *r_ret);

	mesh_variant (*call_method)(mesh_pluginscript_instance_data *p_data,
			const mesh_string_name *p_method, const mesh_variant **p_args,
			int p_argcount, mesh_variant_call_error *r_error);

	void (*notification)(mesh_pluginscript_instance_data *p_data, int p_notification);
	mesh_string (*to_string)(mesh_pluginscript_instance_data *p_data, mesh_bool *r_valid);

	//this is used by script languages that keep a reference counter of their own
	//you can make make Ref<> not die when it reaches zero, so deleting the reference
	//depends entirely from the script.
	// Note: You can set those function pointer to nullptr if not needed.
	void (*refcount_incremented)(mesh_pluginscript_instance_data *p_data);
	bool (*refcount_decremented)(mesh_pluginscript_instance_data *p_data); // return true if it can die
} mesh_pluginscript_instance_desc;

// --- Script ---

typedef struct {
	mesh_pluginscript_script_data *data;
	mesh_string_name name;
	mesh_bool is_tool;
	mesh_string_name base;
	mesh_string icon_path;

	// Member lines format: {<string>: <int>}
	mesh_dictionary member_lines;
	// Method info dictionary format
	// {
	//  name: <string>
	//  args: [<dict:property>]
	//  default_args: [<variant>]
	//  return: <dict:property>
	//  flags: <int>
	//  rpc_mode: <int:mesh_method_rpc_mode>
	// }
	mesh_array methods;
	// Same format than for methods
	mesh_array signals;
	// Property info dictionary format
	// {
	//  name: <string>
	//  type: <int:mesh_variant_type>
	//  hint: <int:mesh_property_hint>
	//  hint_string: <string>
	//  usage: <int:mesh_property_usage_flags>
	//  default_value: <variant>
	//  rset_mode: <int:mesh_method_rpc_mode>
	// }
	mesh_array properties;
} mesh_pluginscript_script_manifest;

typedef struct {
	mesh_pluginscript_script_manifest (*init)(mesh_pluginscript_language_data *p_data, const mesh_string *p_path, const mesh_string *p_source, mesh_error *r_error);
	void (*finish)(mesh_pluginscript_script_data *p_data);
	mesh_pluginscript_instance_desc instance_desc;
} mesh_pluginscript_script_desc;

// --- Language ---

typedef struct {
	mesh_string_name signature;
	mesh_int call_count;
	mesh_int total_time; // In microseconds
	mesh_int self_time; // In microseconds
} mesh_pluginscript_profiling_data;

typedef struct {
	const char *name;
	const char *type;
	const char *extension;
	const char **recognized_extensions; // nullptr terminated array
	mesh_pluginscript_language_data *(*init)();
	void (*finish)(mesh_pluginscript_language_data *p_data);
	const char **reserved_words; // nullptr terminated array
	const char **comment_delimiters; // nullptr terminated array
	const char **string_delimiters; // nullptr terminated array
	mesh_bool has_named_classes;
	mesh_bool supports_builtin_mode;
	mesh_bool can_inherit_from_file;

	mesh_string (*get_template_source_code)(mesh_pluginscript_language_data *p_data, const mesh_string *p_class_name, const mesh_string *p_base_class_name);
	mesh_bool (*validate)(mesh_pluginscript_language_data *p_data, const mesh_string *p_script, const mesh_string *p_path, mesh_packed_string_array *r_functions, mesh_array *r_errors); // errors = Array of Dictionary with "line", "column", "message" keys
	int (*find_function)(mesh_pluginscript_language_data *p_data, const mesh_string *p_function, const mesh_string *p_code); // Can be nullptr
	mesh_string (*make_function)(mesh_pluginscript_language_data *p_data, const mesh_string *p_class, const mesh_string *p_name, const mesh_packed_string_array *p_args);
	mesh_error (*complete_code)(mesh_pluginscript_language_data *p_data, const mesh_string *p_code, const mesh_string *p_path, mesh_object *p_owner, mesh_array *r_options, mesh_bool *r_force, mesh_string *r_call_hint);
	void (*auto_indent_code)(mesh_pluginscript_language_data *p_data, mesh_string *p_code, int p_from_line, int p_to_line);

	void (*add_global_constant)(mesh_pluginscript_language_data *p_data, const mesh_string_name *p_variable, const mesh_variant *p_value);
	mesh_string (*debug_get_error)(mesh_pluginscript_language_data *p_data);
	int (*debug_get_stack_level_count)(mesh_pluginscript_language_data *p_data);
	int (*debug_get_stack_level_line)(mesh_pluginscript_language_data *p_data, int p_level);
	mesh_string (*debug_get_stack_level_function)(mesh_pluginscript_language_data *p_data, int p_level);
	mesh_string (*debug_get_stack_level_source)(mesh_pluginscript_language_data *p_data, int p_level);
	void (*debug_get_stack_level_locals)(mesh_pluginscript_language_data *p_data, int p_level, mesh_packed_string_array *p_locals, mesh_array *p_values, int p_max_subitems, int p_max_depth);
	void (*debug_get_stack_level_members)(mesh_pluginscript_language_data *p_data, int p_level, mesh_packed_string_array *p_members, mesh_array *p_values, int p_max_subitems, int p_max_depth);
	void (*debug_get_globals)(mesh_pluginscript_language_data *p_data, mesh_packed_string_array *p_locals, mesh_array *p_values, int p_max_subitems, int p_max_depth);
	mesh_string (*debug_parse_stack_level_expression)(mesh_pluginscript_language_data *p_data, int p_level, const mesh_string *p_expression, int p_max_subitems, int p_max_depth);

	// TODO: could this stuff be moved to the mesh_pluginscript_language_desc ?
	void (*get_public_functions)(mesh_pluginscript_language_data *p_data, mesh_array *r_functions);
	void (*get_public_constants)(mesh_pluginscript_language_data *p_data, mesh_dictionary *r_constants);

	void (*profiling_start)(mesh_pluginscript_language_data *p_data);
	void (*profiling_stop)(mesh_pluginscript_language_data *p_data);
	int (*profiling_get_accumulated_data)(mesh_pluginscript_language_data *p_data, mesh_pluginscript_profiling_data *r_info, int p_info_max);
	int (*profiling_get_frame_data)(mesh_pluginscript_language_data *p_data, mesh_pluginscript_profiling_data *r_info, int p_info_max);
	void (*profiling_frame)(mesh_pluginscript_language_data *p_data);

	mesh_pluginscript_script_desc script_desc;
} mesh_pluginscript_language_desc;

void GDAPI mesh_pluginscript_register_language(const mesh_pluginscript_language_desc *language_desc);

#ifdef __cplusplus
}
#endif

#endif // MESH_PLUGINSCRIPT_H
