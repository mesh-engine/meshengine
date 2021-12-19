/*************************************************************************/
/*  rid.h                                                                */
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

#ifndef MESH_RID_H
#define MESH_RID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MESH_RID_SIZE sizeof(uint64_t)

#ifndef MESH_CORE_API_MESH_RID_TYPE_DEFINED
#define MESH_CORE_API_MESH_RID_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_RID_SIZE];
} mesh_rid;
#endif

#include <gdnative/gdnative.h>

void GDAPI mesh_rid_new(mesh_rid *p_self);
void GDAPI mesh_rid_new_copy(mesh_rid *r_dest, const mesh_rid *p_src);

#ifdef __cplusplus
}
#endif

#endif // MESH_RID_H
