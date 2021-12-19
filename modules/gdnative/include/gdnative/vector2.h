/*************************************************************************/
/*  vector2.h                                                            */
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

#ifndef MESH_VECTOR2_H
#define MESH_VECTOR2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gdnative/math_defs.h>

#define MESH_VECTOR2_SIZE (sizeof(mesh_real_t) * 2)

#ifndef MESH_CORE_API_MESH_VECTOR2_TYPE_DEFINED
#define MESH_CORE_API_MESH_VECTOR2_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_VECTOR2_SIZE];
} mesh_vector2;
#endif

#define MESH_VECTOR2I_SIZE (sizeof(int32_t) * 2)

#ifndef MESH_CORE_API_MESH_VECTOR2I_TYPE_DEFINED
#define MESH_CORE_API_MESH_VECTOR2I_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_VECTOR2I_SIZE];
} mesh_vector2i;
#endif

#include <gdnative/gdnative.h>

void GDAPI mesh_vector2_new(mesh_vector2 *p_self);
void GDAPI mesh_vector2_new_copy(mesh_vector2 *r_dest, const mesh_vector2 *p_src);
void GDAPI mesh_vector2i_new(mesh_vector2i *p_self);
void GDAPI mesh_vector2i_new_copy(mesh_vector2i *r_dest, const mesh_vector2i *p_src);
mesh_real_t GDAPI *mesh_vector2_operator_index(mesh_vector2 *p_self, mesh_int p_index);
const mesh_real_t GDAPI *mesh_vector2_operator_index_const(const mesh_vector2 *p_self, mesh_int p_index);
int32_t GDAPI *mesh_vector2i_operator_index(mesh_vector2i *p_self, mesh_int p_index);
const int32_t GDAPI *mesh_vector2i_operator_index_const(const mesh_vector2i *p_self, mesh_int p_index);

#ifdef __cplusplus
}
#endif

#endif // MESH_VECTOR2_H
