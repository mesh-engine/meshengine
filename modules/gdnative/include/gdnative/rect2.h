/*************************************************************************/
/*  rect2.h                                                              */
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

#ifndef MESH_RECT2_H
#define MESH_RECT2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gdnative/math_defs.h>

#define MESH_RECT2_SIZE (sizeof(mesh_real_t) * 4)

#ifndef MESH_CORE_API_MESH_RECT2_TYPE_DEFINED
#define MESH_CORE_API_MESH_RECT2_TYPE_DEFINED
typedef struct mesh_rect2 {
	uint8_t _dont_touch_that[MESH_RECT2_SIZE];
} mesh_rect2;
#endif

#define MESH_RECT2I_SIZE (sizeof(int32_t) * 4)

#ifndef MESH_CORE_API_MESH_RECT2I_TYPE_DEFINED
#define MESH_CORE_API_MESH_RECT2I_TYPE_DEFINED
typedef struct mesh_rect2i {
	uint8_t _dont_touch_that[MESH_RECT2I_SIZE];
} mesh_rect2i;
#endif

#include <gdnative/gdnative.h>

void GDAPI mesh_rect2_new(mesh_rect2 *p_self);
void GDAPI mesh_rect2_new_copy(mesh_rect2 *r_dest, const mesh_rect2 *p_src);
void GDAPI mesh_rect2i_new(mesh_rect2i *p_self);
void GDAPI mesh_rect2i_new_copy(mesh_rect2i *r_dest, const mesh_rect2i *p_src);

#ifdef __cplusplus
}
#endif

#endif // MESH_RECT2_H
