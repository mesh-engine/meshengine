/*************************************************************************/
/*  packed_arrays.h                                                      */
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

#ifndef MESH_PACKED_ARRAYS_H
#define MESH_PACKED_ARRAYS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/////// PackedByteArray

#define MESH_PACKED_BYTE_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_BYTE_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_BYTE_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_BYTE_ARRAY_SIZE];
} mesh_packed_byte_array;
#endif

/////// PackedInt32Array

#define MESH_PACKED_INT32_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_INT32_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_INT32_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_INT32_ARRAY_SIZE];
} mesh_packed_int32_array;
#endif

/////// PackedInt64Array

#define MESH_PACKED_INT64_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_INT64_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_INT64_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_INT64_ARRAY_SIZE];
} mesh_packed_int64_array;
#endif

/////// PackedFloat32Array

#define MESH_PACKED_FLOAT32_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_FLOAT32_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_FLOAT32_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_FLOAT32_ARRAY_SIZE];
} mesh_packed_float32_array;
#endif

/////// PackedFloat64Array

#define MESH_PACKED_FLOAT64_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_FLOAT64_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_FLOAT64_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_FLOAT64_ARRAY_SIZE];
} mesh_packed_float64_array;
#endif

/////// PackedStringArray

#define MESH_PACKED_STRING_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_STRING_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_STRING_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_STRING_ARRAY_SIZE];
} mesh_packed_string_array;
#endif

/////// PackedVector2Array

#define MESH_PACKED_VECTOR2_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_VECTOR2_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_VECTOR2_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_VECTOR2_ARRAY_SIZE];
} mesh_packed_vector2_array;
#endif

/////// PackedVector2iArray

#define MESH_PACKED_VECTOR2I_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_VECTOR2I_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_VECTOR2I_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_VECTOR2I_ARRAY_SIZE];
} mesh_packed_vector2i_array;
#endif

/////// PackedVector3Array

#define MESH_PACKED_VECTOR3_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_VECTOR3_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_VECTOR3_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_VECTOR3_ARRAY_SIZE];
} mesh_packed_vector3_array;
#endif

/////// PackedVector3iArray

#define MESH_PACKED_VECTOR3I_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_VECTOR3I_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_VECTOR3I_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_VECTOR3I_ARRAY_SIZE];
} mesh_packed_vector3i_array;
#endif

/////// PackedColorArray

#define MESH_PACKED_COLOR_ARRAY_SIZE (2 * sizeof(void *))

#ifndef MESH_CORE_API_MESH_PACKED_COLOR_ARRAY_TYPE_DEFINED
#define MESH_CORE_API_MESH_PACKED_COLOR_ARRAY_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_PACKED_COLOR_ARRAY_SIZE];
} mesh_packed_color_array;
#endif

#include <gdnative/gdnative.h>

// Byte.

void GDAPI mesh_packed_byte_array_new(mesh_packed_byte_array *p_self);
void GDAPI mesh_packed_byte_array_new_copy(mesh_packed_byte_array *r_dest, const mesh_packed_byte_array *p_src);
void GDAPI mesh_packed_byte_array_destroy(mesh_packed_byte_array *p_self);
uint8_t GDAPI *mesh_packed_byte_array_operator_index(mesh_packed_byte_array *p_self, mesh_int p_index);
const uint8_t GDAPI *mesh_packed_byte_array_operator_index_const(const mesh_packed_byte_array *p_self, mesh_int p_index);

// Int32.

void GDAPI mesh_packed_int32_array_new(mesh_packed_int32_array *p_self);
void GDAPI mesh_packed_int32_array_new_copy(mesh_packed_int32_array *r_dest, const mesh_packed_int32_array *p_src);
void GDAPI mesh_packed_int32_array_destroy(mesh_packed_int32_array *p_self);
int32_t GDAPI *mesh_packed_int32_array_operator_index(mesh_packed_int32_array *p_self, mesh_int p_index);
const int32_t GDAPI *mesh_packed_int32_array_operator_index_const(const mesh_packed_int32_array *p_self, mesh_int p_index);

// Int64.

void GDAPI mesh_packed_int64_array_new(mesh_packed_int64_array *p_self);
void GDAPI mesh_packed_int64_array_new_copy(mesh_packed_int64_array *r_dest, const mesh_packed_int64_array *p_src);
void GDAPI mesh_packed_int64_array_destroy(mesh_packed_int64_array *p_self);
int64_t GDAPI *mesh_packed_int64_array_operator_index(mesh_packed_int64_array *p_self, mesh_int p_index);
const int64_t GDAPI *mesh_packed_int64_array_operator_index_const(const mesh_packed_int64_array *p_self, mesh_int p_index);

// Float32.

void GDAPI mesh_packed_float32_array_new(mesh_packed_float32_array *p_self);
void GDAPI mesh_packed_float32_array_new_copy(mesh_packed_float32_array *r_dest, const mesh_packed_float32_array *p_src);
void GDAPI mesh_packed_float32_array_destroy(mesh_packed_float32_array *p_self);
float GDAPI *mesh_packed_float32_array_operator_index(mesh_packed_float32_array *p_self, mesh_int p_index);
const float GDAPI *mesh_packed_float32_array_operator_index_const(const mesh_packed_float32_array *p_self, mesh_int p_index);

// Float64.

void GDAPI mesh_packed_float64_array_new(mesh_packed_float64_array *p_self);
void GDAPI mesh_packed_float64_array_new_copy(mesh_packed_float64_array *r_dest, const mesh_packed_float64_array *p_src);
void GDAPI mesh_packed_float64_array_destroy(mesh_packed_float64_array *p_self);
double GDAPI *mesh_packed_float64_array_operator_index(mesh_packed_float64_array *p_self, mesh_int p_index);
const double GDAPI *mesh_packed_float64_array_operator_index_const(const mesh_packed_float64_array *p_self, mesh_int p_index);

// String.

void GDAPI mesh_packed_string_array_new(mesh_packed_string_array *p_self);
void GDAPI mesh_packed_string_array_new_copy(mesh_packed_string_array *r_dest, const mesh_packed_string_array *p_src);
void GDAPI mesh_packed_string_array_destroy(mesh_packed_string_array *p_self);
mesh_string GDAPI *mesh_packed_string_array_operator_index(mesh_packed_string_array *p_self, mesh_int p_index);
const mesh_string GDAPI *mesh_packed_string_array_operator_index_const(const mesh_packed_string_array *p_self, mesh_int p_index);

// Vector2.

void GDAPI mesh_packed_vector2_array_new(mesh_packed_vector2_array *p_self);
void GDAPI mesh_packed_vector2_array_new_copy(mesh_packed_vector2_array *r_dest, const mesh_packed_vector2_array *p_src);
void GDAPI mesh_packed_vector2_array_destroy(mesh_packed_vector2_array *p_self);
mesh_vector2 GDAPI *mesh_packed_vector2_array_operator_index(mesh_packed_vector2_array *p_self, mesh_int p_index);
const mesh_vector2 GDAPI *mesh_packed_vector2_array_operator_index_const(const mesh_packed_vector2_array *p_self, mesh_int p_index);

// Vector2i.

void GDAPI mesh_packed_vector2i_array_new(mesh_packed_vector2i_array *p_self);
void GDAPI mesh_packed_vector2i_array_new_copy(mesh_packed_vector2i_array *r_dest, const mesh_packed_vector2i_array *p_src);
void GDAPI mesh_packed_vector2i_array_destroy(mesh_packed_vector2i_array *p_self);
mesh_vector2i GDAPI *mesh_packed_vector2i_array_operator_index(mesh_packed_vector2i_array *p_self, mesh_int p_index);
const mesh_vector2i GDAPI *mesh_packed_vector2i_array_operator_index_const(const mesh_packed_vector2i_array *p_self, mesh_int p_index);

// Vector3.

void GDAPI mesh_packed_vector3_array_new(mesh_packed_vector3_array *p_self);
void GDAPI mesh_packed_vector3_array_new_copy(mesh_packed_vector3_array *r_dest, const mesh_packed_vector3_array *p_src);
void GDAPI mesh_packed_vector3_array_destroy(mesh_packed_vector3_array *p_self);
mesh_vector3 GDAPI *mesh_packed_vector3_array_operator_index(mesh_packed_vector3_array *p_self, mesh_int p_index);
const mesh_vector3 GDAPI *mesh_packed_vector3_array_operator_index_const(const mesh_packed_vector3_array *p_self, mesh_int p_index);

// Vector3i.

void GDAPI mesh_packed_vector3i_array_new(mesh_packed_vector3i_array *p_self);
void GDAPI mesh_packed_vector3i_array_new_copy(mesh_packed_vector3i_array *r_dest, const mesh_packed_vector3i_array *p_src);
void GDAPI mesh_packed_vector3i_array_destroy(mesh_packed_vector3i_array *p_self);
mesh_vector3i GDAPI *mesh_packed_vector3i_array_operator_index(mesh_packed_vector3i_array *p_self, mesh_int p_index);
const mesh_vector3i GDAPI *mesh_packed_vector3i_array_operator_index_const(const mesh_packed_vector3i_array *p_self, mesh_int p_index);

// Color.

void GDAPI mesh_packed_color_array_new(mesh_packed_color_array *p_self);
void GDAPI mesh_packed_color_array_new_copy(mesh_packed_color_array *r_dest, const mesh_packed_color_array *p_src);
void GDAPI mesh_packed_color_array_destroy(mesh_packed_color_array *p_self);
mesh_color GDAPI *mesh_packed_color_array_operator_index(mesh_packed_color_array *p_self, mesh_int p_index);
const mesh_color GDAPI *mesh_packed_color_array_operator_index_const(const mesh_packed_color_array *p_self, mesh_int p_index);

#ifdef __cplusplus
}
#endif

#endif // MESH_PACKED_ARRAYS_H
