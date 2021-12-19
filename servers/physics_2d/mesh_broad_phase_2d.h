/*************************************************************************/
/*  mesh_broad_phase_2d.h                                               */
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

#ifndef MESH_BROAD_PHASE_2D_H
#define MESH_BROAD_PHASE_2D_H

#include "core/math/math_funcs.h"
#include "core/math/rect2.h"

class MeshCollisionObject2D;

class MeshBroadPhase2D {
public:
	typedef MeshBroadPhase2D *(*CreateFunction)();

	static CreateFunction create_func;

	typedef uint32_t ID;

	typedef void *(*PairCallback)(MeshCollisionObject2D *A, int p_subindex_A, MeshCollisionObject2D *B, int p_subindex_B, void *p_userdata);
	typedef void (*UnpairCallback)(MeshCollisionObject2D *A, int p_subindex_A, MeshCollisionObject2D *B, int p_subindex_B, void *p_data, void *p_userdata);

	// 0 is an invalid ID
	virtual ID create(MeshCollisionObject2D *p_object_, int p_subindex = 0, const Rect2 &p_aabb = Rect2(), bool p_static = false) = 0;
	virtual void move(ID p_id, const Rect2 &p_aabb) = 0;
	virtual void set_static(ID p_id, bool p_static) = 0;
	virtual void remove(ID p_id) = 0;

	virtual MeshCollisionObject2D *get_object(ID p_id) const = 0;
	virtual bool is_static(ID p_id) const = 0;
	virtual int get_subindex(ID p_id) const = 0;

	virtual int cull_segment(const Vector2 &p_from, const Vector2 &p_to, MeshCollisionObject2D **p_results, int p_max_results, int *p_result_indices = nullptr) = 0;
	virtual int cull_aabb(const Rect2 &p_aabb, MeshCollisionObject2D **p_results, int p_max_results, int *p_result_indices = nullptr) = 0;

	virtual void set_pair_callback(PairCallback p_pair_callback, void *p_userdata) = 0;
	virtual void set_unpair_callback(UnpairCallback p_unpair_callback, void *p_userdata) = 0;

	virtual void update() = 0;

	virtual ~MeshBroadPhase2D();
};

#endif // MESH_BROAD_PHASE_2D_H
