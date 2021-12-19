/*************************************************************************/
/*  variant.h                                                            */
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

#ifndef MESH_VARIANT_H
#define MESH_VARIANT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gdnative/math_defs.h>
#include <gdnative/variant_struct.h>

typedef enum mesh_variant_type {
	MESH_VARIANT_TYPE_NIL,

	// atomic types
	MESH_VARIANT_TYPE_BOOL,
	MESH_VARIANT_TYPE_INT,
	MESH_VARIANT_TYPE_FLOAT,
	MESH_VARIANT_TYPE_STRING,

	// math types
	MESH_VARIANT_TYPE_VECTOR2,
	MESH_VARIANT_TYPE_VECTOR2I,
	MESH_VARIANT_TYPE_RECT2,
	MESH_VARIANT_TYPE_RECT2I,
	MESH_VARIANT_TYPE_VECTOR3,
	MESH_VARIANT_TYPE_VECTOR3I,
	MESH_VARIANT_TYPE_TRANSFORM2D,
	MESH_VARIANT_TYPE_PLANE,
	MESH_VARIANT_TYPE_QUATERNION,
	MESH_VARIANT_TYPE_AABB,
	MESH_VARIANT_TYPE_BASIS,
	MESH_VARIANT_TYPE_TRANSFORM3D,

	// misc types
	MESH_VARIANT_TYPE_COLOR,
	MESH_VARIANT_TYPE_STRING_NAME,
	MESH_VARIANT_TYPE_NODE_PATH,
	MESH_VARIANT_TYPE_RID,
	MESH_VARIANT_TYPE_OBJECT,
	MESH_VARIANT_TYPE_CALLABLE,
	MESH_VARIANT_TYPE_SIGNAL,
	MESH_VARIANT_TYPE_DICTIONARY,
	MESH_VARIANT_TYPE_ARRAY,

	// arrays
	MESH_VARIANT_TYPE_PACKED_BYTE_ARRAY,
	MESH_VARIANT_TYPE_PACKED_INT32_ARRAY,
	MESH_VARIANT_TYPE_PACKED_INT64_ARRAY,
	MESH_VARIANT_TYPE_PACKED_FLOAT32_ARRAY,
	MESH_VARIANT_TYPE_PACKED_FLOAT64_ARRAY,
	MESH_VARIANT_TYPE_PACKED_STRING_ARRAY,
	MESH_VARIANT_TYPE_PACKED_VECTOR2_ARRAY,
	MESH_VARIANT_TYPE_PACKED_VECTOR3_ARRAY,
	MESH_VARIANT_TYPE_PACKED_COLOR_ARRAY,
} mesh_variant_type;

typedef enum mesh_variant_call_error_error {
	MESH_CALL_ERROR_CALL_OK,
	MESH_CALL_ERROR_CALL_ERROR_INVALID_METHOD,
	MESH_CALL_ERROR_CALL_ERROR_INVALID_ARGUMENT,
	MESH_CALL_ERROR_CALL_ERROR_TOO_MANY_ARGUMENTS,
	MESH_CALL_ERROR_CALL_ERROR_TOO_FEW_ARGUMENTS,
	MESH_CALL_ERROR_CALL_ERROR_INSTANCE_IS_NULL,
} mesh_variant_call_error_error;

typedef struct mesh_variant_call_error {
	mesh_variant_call_error_error error;
	int argument;
	mesh_variant_type expected;
} mesh_variant_call_error;

typedef enum mesh_variant_operator {
	// comparison
	MESH_VARIANT_OP_EQUAL,
	MESH_VARIANT_OP_NOT_EQUAL,
	MESH_VARIANT_OP_LESS,
	MESH_VARIANT_OP_LESS_EQUAL,
	MESH_VARIANT_OP_GREATER,
	MESH_VARIANT_OP_GREATER_EQUAL,

	// mathematic
	MESH_VARIANT_OP_ADD,
	MESH_VARIANT_OP_SUBTRACT,
	MESH_VARIANT_OP_MULTIPLY,
	MESH_VARIANT_OP_DIVIDE,
	MESH_VARIANT_OP_NEGATE,
	MESH_VARIANT_OP_POSITIVE,
	MESH_VARIANT_OP_MODULE,
	MESH_VARIANT_OP_STRING_CONCAT,

	// bitwise
	MESH_VARIANT_OP_SHIFT_LEFT,
	MESH_VARIANT_OP_SHIFT_RIGHT,
	MESH_VARIANT_OP_BIT_AND,
	MESH_VARIANT_OP_BIT_OR,
	MESH_VARIANT_OP_BIT_XOR,
	MESH_VARIANT_OP_BIT_NEGATE,

	// logic
	MESH_VARIANT_OP_AND,
	MESH_VARIANT_OP_OR,
	MESH_VARIANT_OP_XOR,
	MESH_VARIANT_OP_NOT,

	// containment
	MESH_VARIANT_OP_IN,

	MESH_VARIANT_OP_MAX,
} mesh_variant_operator;

typedef enum mesh_variant_utility_function_type {
	MESH_UTILITY_FUNC_TYPE_MATH,
	MESH_UTILITY_FUNC_TYPE_RANDOM,
	MESH_UTILITY_FUNC_TYPE_GENERAL,
} mesh_variant_utility_function_type;

// Types for function pointers.
typedef void (*mesh_validated_operator_evaluator)(const mesh_variant *p_left, const mesh_variant *p_right, mesh_variant *r_result);
typedef void (*mesh_ptr_operator_evaluator)(const void *p_left, const void *p_right, void *r_result);
typedef void (*mesh_validated_builtin_method)(mesh_variant *p_base, const mesh_variant **p_args, int p_argument_count, mesh_variant *r_return);
typedef void (*mesh_ptr_builtin_method)(void *p_base, const void **p_args, void *r_return, int p_argument_count);
typedef void (*mesh_validated_constructor)(mesh_variant *p_base, const mesh_variant **p_args);
typedef void (*mesh_ptr_constructor)(void *p_base, const void **p_args);
typedef void (*mesh_validated_setter)(mesh_variant *p_base, const mesh_variant *p_value);
typedef void (*mesh_validated_getter)(const mesh_variant *p_base, mesh_variant *r_value);
typedef void (*mesh_ptr_setter)(void *p_base, const void *p_value);
typedef void (*mesh_ptr_getter)(const void *p_base, void *r_value);
typedef void (*mesh_validated_indexed_setter)(mesh_variant *p_base, mesh_int p_index, const mesh_variant *p_value, bool *r_oob);
typedef void (*mesh_validated_indexed_getter)(const mesh_variant *p_base, mesh_int p_index, mesh_variant *r_value, bool *r_oob);
typedef void (*mesh_ptr_indexed_setter)(void *p_base, mesh_int p_index, const void *p_value);
typedef void (*mesh_ptr_indexed_getter)(const void *p_base, mesh_int p_index, void *r_value);
typedef void (*mesh_validated_keyed_setter)(mesh_variant *p_base, const mesh_variant *p_key, const mesh_variant *p_value, bool *r_valid);
typedef void (*mesh_validated_keyed_getter)(const mesh_variant *p_base, const mesh_variant *p_key, mesh_variant *r_value, bool *r_valid);
typedef bool (*mesh_validated_keyed_checker)(const mesh_variant *p_base, const mesh_variant *p_key, bool *r_valid);
typedef void (*mesh_ptr_keyed_setter)(void *p_base, const void *p_key, const void *p_value);
typedef void (*mesh_ptr_keyed_getter)(const void *p_base, const void *p_key, void *r_value);
typedef uint32_t (*mesh_ptr_keyed_checker)(const mesh_variant *p_base, const mesh_variant *p_key);
typedef void (*mesh_validated_utility_function)(mesh_variant *r_return, const mesh_variant **p_arguments, int p_argument_count);
typedef void (*mesh_ptr_utility_function)(void *r_return, const void **p_arguments, int p_argument_count);

#include <gdnative/aabb.h>
#include <gdnative/array.h>
#include <gdnative/basis.h>
#include <gdnative/callable.h>
#include <gdnative/color.h>
#include <gdnative/dictionary.h>
#include <gdnative/node_path.h>
#include <gdnative/packed_arrays.h>
#include <gdnative/plane.h>
#include <gdnative/quaternion.h>
#include <gdnative/rect2.h>
#include <gdnative/rid.h>
#include <gdnative/signal.h>
#include <gdnative/string.h>
#include <gdnative/string_name.h>
#include <gdnative/transform2d.h>
#include <gdnative/transform_3d.h>
#include <gdnative/variant.h>
#include <gdnative/vector2.h>
#include <gdnative/vector3.h>

#include <gdnative/gdnative.h>

// Memory.

void GDAPI mesh_variant_new_copy(mesh_variant *r_dest, const mesh_variant *p_src);

void GDAPI mesh_variant_new_nil(mesh_variant *r_dest);
void GDAPI mesh_variant_new_bool(mesh_variant *r_dest, const mesh_bool p_b);
void GDAPI mesh_variant_new_int(mesh_variant *r_dest, const mesh_int p_i);
void GDAPI mesh_variant_new_float(mesh_variant *r_dest, const mesh_float p_f);
void GDAPI mesh_variant_new_string(mesh_variant *r_dest, const mesh_string *p_s);
void GDAPI mesh_variant_new_vector2(mesh_variant *r_dest, const mesh_vector2 *p_v2);
void GDAPI mesh_variant_new_vector2i(mesh_variant *r_dest, const mesh_vector2i *p_v2);
void GDAPI mesh_variant_new_rect2(mesh_variant *r_dest, const mesh_rect2 *p_rect2);
void GDAPI mesh_variant_new_rect2i(mesh_variant *r_dest, const mesh_rect2i *p_rect2);
void GDAPI mesh_variant_new_vector3(mesh_variant *r_dest, const mesh_vector3 *p_v3);
void GDAPI mesh_variant_new_vector3i(mesh_variant *r_dest, const mesh_vector3i *p_v3);
void GDAPI mesh_variant_new_transform2d(mesh_variant *r_dest, const mesh_transform2d *p_t2d);
void GDAPI mesh_variant_new_plane(mesh_variant *r_dest, const mesh_plane *p_plane);
void GDAPI mesh_variant_new_quaternion(mesh_variant *r_dest, const mesh_quaternion *p_quaternion);
void GDAPI mesh_variant_new_aabb(mesh_variant *r_dest, const mesh_aabb *p_aabb);
void GDAPI mesh_variant_new_basis(mesh_variant *r_dest, const mesh_basis *p_basis);
void GDAPI mesh_variant_new_transform3d(mesh_variant *r_dest, const mesh_transform3d *p_trans);
void GDAPI mesh_variant_new_color(mesh_variant *r_dest, const mesh_color *p_color);
void GDAPI mesh_variant_new_string_name(mesh_variant *r_dest, const mesh_string_name *p_s);
void GDAPI mesh_variant_new_node_path(mesh_variant *r_dest, const mesh_node_path *p_np);
void GDAPI mesh_variant_new_rid(mesh_variant *r_dest, const mesh_rid *p_rid);
void GDAPI mesh_variant_new_object(mesh_variant *r_dest, const mesh_object *p_obj);
void GDAPI mesh_variant_new_callable(mesh_variant *r_dest, const mesh_callable *p_callable);
void GDAPI mesh_variant_new_signal(mesh_variant *r_dest, const mesh_signal *p_signal);
void GDAPI mesh_variant_new_dictionary(mesh_variant *r_dest, const mesh_dictionary *p_dict);
void GDAPI mesh_variant_new_array(mesh_variant *r_dest, const mesh_array *p_arr);
void GDAPI mesh_variant_new_packed_byte_array(mesh_variant *r_dest, const mesh_packed_byte_array *p_pba);
void GDAPI mesh_variant_new_packed_int32_array(mesh_variant *r_dest, const mesh_packed_int32_array *p_pia);
void GDAPI mesh_variant_new_packed_int64_array(mesh_variant *r_dest, const mesh_packed_int64_array *p_pia);
void GDAPI mesh_variant_new_packed_float32_array(mesh_variant *r_dest, const mesh_packed_float32_array *p_pra);
void GDAPI mesh_variant_new_packed_float64_array(mesh_variant *r_dest, const mesh_packed_float64_array *p_pra);
void GDAPI mesh_variant_new_packed_string_array(mesh_variant *r_dest, const mesh_packed_string_array *p_psa);
void GDAPI mesh_variant_new_packed_vector2_array(mesh_variant *r_dest, const mesh_packed_vector2_array *p_pv2a);
void GDAPI mesh_variant_new_packed_vector3_array(mesh_variant *r_dest, const mesh_packed_vector3_array *p_pv3a);
void GDAPI mesh_variant_new_packed_color_array(mesh_variant *r_dest, const mesh_packed_color_array *p_pca);

mesh_bool GDAPI mesh_variant_as_bool(const mesh_variant *p_self);
mesh_int GDAPI mesh_variant_as_int(const mesh_variant *p_self);
mesh_float GDAPI mesh_variant_as_float(const mesh_variant *p_self);
mesh_string GDAPI mesh_variant_as_string(const mesh_variant *p_self);
mesh_vector2 GDAPI mesh_variant_as_vector2(const mesh_variant *p_self);
mesh_vector2i GDAPI mesh_variant_as_vector2i(const mesh_variant *p_self);
mesh_rect2 GDAPI mesh_variant_as_rect2(const mesh_variant *p_self);
mesh_rect2i GDAPI mesh_variant_as_rect2i(const mesh_variant *p_self);
mesh_vector3 GDAPI mesh_variant_as_vector3(const mesh_variant *p_self);
mesh_vector3i GDAPI mesh_variant_as_vector3i(const mesh_variant *p_self);
mesh_transform2d GDAPI mesh_variant_as_transform2d(const mesh_variant *p_self);
mesh_plane GDAPI mesh_variant_as_plane(const mesh_variant *p_self);
mesh_quaternion GDAPI mesh_variant_as_quaternion(const mesh_variant *p_self);
mesh_aabb GDAPI mesh_variant_as_aabb(const mesh_variant *p_self);
mesh_basis GDAPI mesh_variant_as_basis(const mesh_variant *p_self);
mesh_transform3d GDAPI mesh_variant_as_transform3d(const mesh_variant *p_self);
mesh_color GDAPI mesh_variant_as_color(const mesh_variant *p_self);
mesh_string_name GDAPI mesh_variant_as_string_name(const mesh_variant *p_self);
mesh_node_path GDAPI mesh_variant_as_node_path(const mesh_variant *p_self);
mesh_rid GDAPI mesh_variant_as_rid(const mesh_variant *p_self);
mesh_object GDAPI *mesh_variant_as_object(const mesh_variant *p_self);
mesh_callable GDAPI mesh_variant_as_callable(const mesh_variant *p_self);
mesh_signal GDAPI mesh_variant_as_signal(const mesh_variant *p_self);
mesh_dictionary GDAPI mesh_variant_as_dictionary(const mesh_variant *p_self);
mesh_array GDAPI mesh_variant_as_array(const mesh_variant *p_self);
mesh_packed_byte_array GDAPI mesh_variant_as_packed_byte_array(const mesh_variant *p_self);
mesh_packed_int32_array GDAPI mesh_variant_as_packed_int32_array(const mesh_variant *p_self);
mesh_packed_int64_array GDAPI mesh_variant_as_packed_int64_array(const mesh_variant *p_self);
mesh_packed_float32_array GDAPI mesh_variant_as_packed_float32_array(const mesh_variant *p_self);
mesh_packed_float64_array GDAPI mesh_variant_as_packed_float64_array(const mesh_variant *p_self);
mesh_packed_string_array GDAPI mesh_variant_as_packed_string_array(const mesh_variant *p_self);
mesh_packed_vector2_array GDAPI mesh_variant_as_packed_vector2_array(const mesh_variant *p_self);
mesh_packed_vector3_array GDAPI mesh_variant_as_packed_vector3_array(const mesh_variant *p_self);
mesh_packed_color_array GDAPI mesh_variant_as_packed_color_array(const mesh_variant *p_self);

void GDAPI mesh_variant_destroy(mesh_variant *p_self);

// Dynamic interaction.

void GDAPI mesh_variant_call(mesh_variant *p_self, const mesh_string_name *p_method, const mesh_variant **p_args, const mesh_int p_argument_count, mesh_variant *r_return, mesh_variant_call_error *r_error);
void GDAPI mesh_variant_call_with_cstring(mesh_variant *p_self, const char *p_method, const mesh_variant **p_args, const mesh_int p_argument_count, mesh_variant *r_return, mesh_variant_call_error *r_error);
void GDAPI mesh_variant_call_static(mesh_variant_type p_type, const mesh_string_name *p_method, const mesh_variant **p_args, const mesh_int p_argument_count, mesh_variant *r_return, mesh_variant_call_error *r_error);
void GDAPI mesh_variant_call_static_with_cstring(mesh_variant_type p_type, const char *p_method, const mesh_variant **p_args, const mesh_int p_argument_count, mesh_variant *r_return, mesh_variant_call_error *r_error);
void GDAPI mesh_variant_evaluate(mesh_variant_operator p_op, const mesh_variant *p_a, const mesh_variant *p_b, mesh_variant *r_return, bool *r_valid);
void GDAPI mesh_variant_set(mesh_variant *p_self, const mesh_variant *p_key, const mesh_variant *p_value, bool *r_valid);
void GDAPI mesh_variant_set_named(mesh_variant *p_self, const mesh_string_name *p_name, const mesh_variant *p_value, bool *r_valid);
void GDAPI mesh_variant_set_named_with_cstring(mesh_variant *p_self, const char *p_name, const mesh_variant *p_value, bool *r_valid);
void GDAPI mesh_variant_set_keyed(mesh_variant *p_self, const mesh_variant *p_key, const mesh_variant *p_value, bool *r_valid);
void GDAPI mesh_variant_set_indexed(mesh_variant *p_self, mesh_int p_index, const mesh_variant *p_value, bool *r_valid, bool *r_oob);
mesh_variant GDAPI mesh_variant_get(const mesh_variant *p_self, const mesh_variant *p_key, bool *r_valid);
mesh_variant GDAPI mesh_variant_get_named(const mesh_variant *p_self, const mesh_string_name *p_key, bool *r_valid);
mesh_variant GDAPI mesh_variant_get_named_with_cstring(const mesh_variant *p_self, const char *p_key, bool *r_valid);
mesh_variant GDAPI mesh_variant_get_keyed(const mesh_variant *p_self, const mesh_variant *p_key, bool *r_valid);
mesh_variant GDAPI mesh_variant_get_indexed(const mesh_variant *p_self, mesh_int p_index, bool *r_valid, bool *r_oob);
/// Iteration.
bool GDAPI mesh_variant_iter_init(const mesh_variant *p_self, mesh_variant *r_iter, bool *r_valid);
bool GDAPI mesh_variant_iter_next(const mesh_variant *p_self, mesh_variant *r_iter, bool *r_valid);
mesh_variant GDAPI mesh_variant_iter_get(const mesh_variant *p_self, mesh_variant *r_iter, bool *r_valid);

/// Variant functions.
mesh_bool GDAPI mesh_variant_hash_compare(const mesh_variant *p_self, const mesh_variant *p_other);
mesh_bool GDAPI mesh_variant_booleanize(const mesh_variant *p_self);
void GDAPI mesh_variant_blend(const mesh_variant *p_a, const mesh_variant *p_b, float p_c, mesh_variant *r_dst);
void GDAPI mesh_variant_interpolate(const mesh_variant *p_a, const mesh_variant *p_b, float p_c, mesh_variant *r_dst);
mesh_variant GDAPI mesh_variant_duplicate(const mesh_variant *p_self, mesh_bool p_deep);
mesh_string GDAPI mesh_variant_stringify(const mesh_variant *p_self);

// Discovery API.

/// Operators.
mesh_validated_operator_evaluator GDAPI mesh_variant_get_validated_operator_evaluator(mesh_variant_operator p_operator, mesh_variant_type p_type_a, mesh_variant_type p_type_b);
mesh_ptr_operator_evaluator GDAPI mesh_variant_get_ptr_operator_evaluator(mesh_variant_operator p_operator, mesh_variant_type p_type_a, mesh_variant_type p_type_b);
mesh_variant_type GDAPI mesh_variant_get_operator_return_type(mesh_variant_operator p_operator, mesh_variant_type p_type_a, mesh_variant_type p_type_b);
mesh_string GDAPI mesh_variant_get_operator_name(mesh_variant_operator p_operator);

/// Built-in methods.
bool GDAPI mesh_variant_has_builtin_method(mesh_variant_type p_type, const mesh_string_name *p_method);
bool GDAPI mesh_variant_has_builtin_method_with_cstring(mesh_variant_type p_type, const char *p_method);
mesh_validated_builtin_method GDAPI mesh_variant_get_validated_builtin_method(mesh_variant_type p_type, const mesh_string_name *p_method);
mesh_validated_builtin_method GDAPI mesh_variant_get_validated_builtin_method_with_cstring(mesh_variant_type p_type, const char *p_method);
mesh_ptr_builtin_method GDAPI mesh_variant_get_ptr_builtin_method(mesh_variant_type p_type, const mesh_string_name *p_method);
mesh_ptr_builtin_method GDAPI mesh_variant_get_ptr_builtin_method_with_cstring(mesh_variant_type p_type, const char *p_method);
int GDAPI mesh_variant_get_builtin_method_argument_count(mesh_variant_type p_type, const mesh_string_name *p_method);
int GDAPI mesh_variant_get_builtin_method_argument_count_with_cstring(mesh_variant_type p_type, const char *p_method);
mesh_variant_type GDAPI mesh_variant_get_builtin_method_argument_type(mesh_variant_type p_type, const mesh_string_name *p_method, int p_argument);
mesh_variant_type GDAPI mesh_variant_get_builtin_method_argument_type_with_cstring(mesh_variant_type p_type, const char *p_method, int p_argument);
mesh_string GDAPI mesh_variant_get_builtin_method_argument_name(mesh_variant_type p_type, const mesh_string_name *p_method, int p_argument);
mesh_string GDAPI mesh_variant_get_builtin_method_argument_name_with_cstring(mesh_variant_type p_type, const char *p_method, int p_argument);
bool GDAPI mesh_variant_has_builtin_method_return_value(mesh_variant_type p_type, const mesh_string_name *p_method);
bool GDAPI mesh_variant_has_builtin_method_return_value_with_cstring(mesh_variant_type p_type, const char *p_method);
mesh_variant_type GDAPI mesh_variant_get_builtin_method_return_type(mesh_variant_type p_type, const mesh_string_name *p_method);
mesh_variant_type GDAPI mesh_variant_get_builtin_method_return_type_with_cstring(mesh_variant_type p_type, const char *p_method);
bool GDAPI mesh_variant_is_builtin_method_const(mesh_variant_type p_type, const mesh_string_name *p_method);
bool GDAPI mesh_variant_is_builtin_method_const_with_cstring(mesh_variant_type p_type, const char *p_method);
bool GDAPI mesh_variant_is_builtin_method_static(mesh_variant_type p_type, const mesh_string_name *p_method);
bool GDAPI mesh_variant_is_builtin_method_static_with_cstring(mesh_variant_type p_type, const char *p_method);
bool GDAPI mesh_variant_is_builtin_method_vararg(mesh_variant_type p_type, const mesh_string_name *p_method);
bool GDAPI mesh_variant_is_builtin_method_vararg_with_cstring(mesh_variant_type p_type, const char *p_method);
int GDAPI mesh_variant_get_builtin_method_count(mesh_variant_type p_type);
void GDAPI mesh_variant_get_builtin_method_list(mesh_variant_type p_type, mesh_string_name *r_list);

/// Constructors.
int GDAPI mesh_variant_get_constructor_count(mesh_variant_type p_type);
mesh_validated_constructor GDAPI mesh_variant_get_validated_constructor(mesh_variant_type p_type, int p_constructor);
mesh_ptr_constructor GDAPI mesh_variant_get_ptr_constructor(mesh_variant_type p_type, int p_constructor);
int GDAPI mesh_variant_get_constructor_argument_count(mesh_variant_type p_type, int p_constructor);
mesh_variant_type GDAPI mesh_variant_get_constructor_argument_type(mesh_variant_type p_type, int p_constructor, int p_argument);
mesh_string GDAPI mesh_variant_get_constructor_argument_name(mesh_variant_type p_type, int p_constructor, int p_argument);
void GDAPI mesh_variant_construct(mesh_variant_type p_type, mesh_variant *p_base, const mesh_variant **p_args, int p_argument_count, mesh_variant_call_error *r_error);

/// Properties.
mesh_variant_type GDAPI mesh_variant_get_member_type(mesh_variant_type p_type, const mesh_string_name *p_member);
mesh_variant_type GDAPI mesh_variant_get_member_type_with_cstring(mesh_variant_type p_type, const char *p_member);
int GDAPI mesh_variant_get_member_count(mesh_variant_type p_type);
void GDAPI mesh_variant_get_member_list(mesh_variant_type p_type, mesh_string_name *r_list);
mesh_validated_setter GDAPI mesh_variant_get_validated_setter(mesh_variant_type p_type, const mesh_string_name *p_member);
mesh_validated_setter GDAPI mesh_variant_get_validated_setter_with_cstring(mesh_variant_type p_type, const char *p_member);
mesh_validated_getter GDAPI mesh_variant_get_validated_getter(mesh_variant_type p_type, const mesh_string_name *p_member);
mesh_validated_getter GDAPI mesh_variant_get_validated_getter_with_cstring(mesh_variant_type p_type, const char *p_member);
mesh_ptr_setter GDAPI mesh_variant_get_ptr_setter(mesh_variant_type p_type, const mesh_string_name *p_member);
mesh_ptr_setter GDAPI mesh_variant_get_ptr_setter_with_cstring(mesh_variant_type p_type, const char *p_member);
mesh_ptr_getter GDAPI mesh_variant_get_ptr_getter(mesh_variant_type p_type, const mesh_string_name *p_member);
mesh_ptr_getter GDAPI mesh_variant_get_ptr_getter_with_cstring(mesh_variant_type p_type, const char *p_member);

/// Indexing.
bool GDAPI mesh_variant_has_indexing(mesh_variant_type p_type);
mesh_variant_type GDAPI mesh_variant_get_indexed_element_type(mesh_variant_type p_type);
mesh_validated_indexed_setter GDAPI mesh_variant_get_validated_indexed_setter(mesh_variant_type p_type);
mesh_validated_indexed_getter GDAPI mesh_variant_get_validated_indexed_getter(mesh_variant_type p_type);
mesh_ptr_indexed_setter GDAPI mesh_variant_get_ptr_indexed_setter(mesh_variant_type p_type);
mesh_ptr_indexed_getter GDAPI mesh_variant_get_ptr_indexed_getter(mesh_variant_type p_type);
uint64_t GDAPI mesh_variant_get_indexed_size(const mesh_variant *p_self);

/// Keying.
bool GDAPI mesh_variant_is_keyed(mesh_variant_type p_type);
mesh_validated_keyed_setter GDAPI mesh_variant_get_validated_keyed_setter(mesh_variant_type p_type);
mesh_validated_keyed_getter GDAPI mesh_variant_get_validated_keyed_getter(mesh_variant_type p_type);
mesh_validated_keyed_checker GDAPI mesh_variant_get_validated_keyed_checker(mesh_variant_type p_type);
mesh_ptr_keyed_setter GDAPI mesh_variant_get_ptr_keyed_setter(mesh_variant_type p_type);
mesh_ptr_keyed_getter GDAPI mesh_variant_get_ptr_keyed_getter(mesh_variant_type p_type);
mesh_ptr_keyed_checker GDAPI mesh_variant_get_ptr_keyed_checker(mesh_variant_type p_type);

/// Constants.
int GDAPI mesh_variant_get_constants_count(mesh_variant_type p_type);
void GDAPI mesh_variant_get_constants_list(mesh_variant_type p_type, mesh_string_name *r_list);
bool GDAPI mesh_variant_has_constant(mesh_variant_type p_type, const mesh_string_name *p_constant);
bool GDAPI mesh_variant_has_constant_with_cstring(mesh_variant_type p_type, const char *p_constant);
mesh_variant GDAPI mesh_variant_get_constant_value(mesh_variant_type p_type, const mesh_string_name *p_constant);
mesh_variant GDAPI mesh_variant_get_constant_value_with_cstring(mesh_variant_type p_type, const char *p_constant);

/// Utilities.
bool GDAPI mesh_variant_has_utility_function(const mesh_string_name *p_function);
bool GDAPI mesh_variant_has_utility_function_with_cstring(const char *p_function);
void GDAPI mesh_variant_call_utility_function(const mesh_string_name *p_function, mesh_variant *r_ret, const mesh_variant **p_args, int p_argument_count, mesh_variant_call_error *r_error);
void GDAPI mesh_variant_call_utility_function_with_cstring(const char *p_function, mesh_variant *r_ret, const mesh_variant **p_args, int p_argument_count, mesh_variant_call_error *r_error);
mesh_ptr_utility_function GDAPI mesh_variant_get_ptr_utility_function(const mesh_string_name *p_function);
mesh_ptr_utility_function GDAPI mesh_variant_get_ptr_utility_function_with_cstring(const char *p_function);
mesh_validated_utility_function GDAPI mesh_variant_get_validated_utility_function(const mesh_string_name *p_function);
mesh_validated_utility_function GDAPI mesh_variant_get_validated_utility_function_with_cstring(const char *p_function);
mesh_variant_utility_function_type GDAPI mesh_variant_get_utility_function_type(const mesh_string_name *p_function);
mesh_variant_utility_function_type GDAPI mesh_variant_get_utility_function_type_with_cstring(const char *p_function);
int GDAPI mesh_variant_get_utility_function_argument_count(const mesh_string_name *p_function);
int GDAPI mesh_variant_get_utility_function_argument_count_with_cstring(const char *p_function);
mesh_variant_type GDAPI mesh_variant_get_utility_function_argument_type(const mesh_string_name *p_function, int p_argument);
mesh_variant_type GDAPI mesh_variant_get_utility_function_argument_type_with_cstring(const char *p_function, int p_argument);
mesh_string GDAPI mesh_variant_get_utility_function_argument_name(const mesh_string_name *p_function, int p_argument);
mesh_string GDAPI mesh_variant_get_utility_function_argument_name_with_cstring(const char *p_function, int p_argument);
bool GDAPI mesh_variant_has_utility_function_return_value(const mesh_string_name *p_function);
bool GDAPI mesh_variant_has_utility_function_return_value_with_cstring(const char *p_function);
mesh_variant_type GDAPI mesh_variant_get_utility_function_return_type(const mesh_string_name *p_function);
mesh_variant_type GDAPI mesh_variant_get_utility_function_return_type_with_cstring(const char *p_function);
bool GDAPI mesh_variant_is_utility_function_vararg(const mesh_string_name *p_function);
bool GDAPI mesh_variant_is_utility_function_vararg_with_cstring(const char *p_function);
int GDAPI mesh_variant_get_utility_function_count();
void GDAPI mesh_variant_get_utility_function_list(mesh_string_name *r_functions);

// Introspection.

mesh_variant_type GDAPI mesh_variant_get_type(const mesh_variant *p_self);
bool GDAPI mesh_variant_has_method(const mesh_variant *p_self, const mesh_string_name *p_method);
bool GDAPI mesh_variant_has_member(mesh_variant_type p_type, const mesh_string_name *p_member);
bool GDAPI mesh_variant_has_key(const mesh_variant *p_self, const mesh_variant *p_key, bool *r_valid);

mesh_string GDAPI mesh_variant_get_type_name(mesh_variant_type p_type);
bool GDAPI mesh_variant_can_convert(mesh_variant_type p_from, mesh_variant_type p_to);
bool GDAPI mesh_variant_can_convert_strict(mesh_variant_type p_from, mesh_variant_type p_to);

#ifdef __cplusplus
}
#endif

#endif
