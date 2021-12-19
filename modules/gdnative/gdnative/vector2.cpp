/*************************************************************************/
/*  vector2.cpp                                                          */
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

#include "gdnative/vector2.h"

#include "core/math/vector2.h"

static_assert(sizeof(mesh_vector2) == sizeof(Vector2), "Vector2 size mismatch");
static_assert(sizeof(mesh_vector2i) == sizeof(Vector2i), "Vector2i size mismatch");

#ifdef __cplusplus
extern "C" {
#endif

void GDAPI mesh_vector2_new(mesh_vector2 *p_self) {
	memnew_placement(p_self, Vector2);
}

void GDAPI mesh_vector2_new_copy(mesh_vector2 *r_dest, const mesh_vector2 *p_src) {
	memnew_placement(r_dest, Vector2(*(Vector2 *)p_src));
}

void GDAPI mesh_vector2i_new(mesh_vector2i *p_self) {
	memnew_placement(p_self, Vector2i);
}

void GDAPI mesh_vector2i_new_copy(mesh_vector2i *r_dest, const mesh_vector2i *p_src) {
	memnew_placement(r_dest, Vector2i(*(Vector2i *)p_src));
}

mesh_real_t GDAPI *mesh_vector2_operator_index(mesh_vector2 *p_self, mesh_int p_index) {
	Vector2 *self = (Vector2 *)p_self;
	return (mesh_real_t *)&self->operator[](p_index);
}

const mesh_real_t GDAPI *mesh_vector2_operator_index_const(const mesh_vector2 *p_self, mesh_int p_index) {
	const Vector2 *self = (const Vector2 *)p_self;
	return (const mesh_real_t *)&self->operator[](p_index);
}

int32_t GDAPI *mesh_vector2i_operator_index(mesh_vector2i *p_self, mesh_int p_index) {
	Vector2i *self = (Vector2i *)p_self;
	return (int32_t *)&self->operator[](p_index);
}

const int32_t GDAPI *mesh_vector2i_operator_index_const(const mesh_vector2i *p_self, mesh_int p_index) {
	const Vector2i *self = (const Vector2i *)p_self;
	return (const int32_t *)&self->operator[](p_index);
}

#ifdef __cplusplus
}
#endif
