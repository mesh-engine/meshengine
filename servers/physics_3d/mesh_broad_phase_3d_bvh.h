/*************************************************************************/
/*  mesh_broad_phase_3d_bvh.h                                           */
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

#ifndef MESH_BROAD_PHASE_3D_BVH_H
#define MESH_BROAD_PHASE_3D_BVH_H

#include "mesh_broad_phase_3d.h"

#include "core/math/bvh.h"

class MeshBroadPhase3DBVH : public MeshBroadPhase3D {
	BVH_Manager<MeshCollisionObject3D, true, 128> bvh;

	static void *_pair_callback(void *, uint32_t, MeshCollisionObject3D *, int, uint32_t, MeshCollisionObject3D *, int);
	static void _unpair_callback(void *, uint32_t, MeshCollisionObject3D *, int, uint32_t, MeshCollisionObject3D *, int, void *);

	PairCallback pair_callback = nullptr;
	void *pair_userdata = nullptr;
	UnpairCallback unpair_callback = nullptr;
	void *unpair_userdata = nullptr;

public:
	// 0 is an invalid ID
	virtual ID create(MeshCollisionObject3D *p_object, int p_subindex = 0, const AABB &p_aabb = AABB(), bool p_static = false);
	virtual void move(ID p_id, const AABB &p_aabb);
	virtual void set_static(ID p_id, bool p_static);
	virtual void remove(ID p_id);

	virtual MeshCollisionObject3D *get_object(ID p_id) const;
	virtual bool is_static(ID p_id) const;
	virtual int get_subindex(ID p_id) const;

	virtual int cull_point(const Vector3 &p_point, MeshCollisionObject3D **p_results, int p_max_results, int *p_result_indices = nullptr);
	virtual int cull_segment(const Vector3 &p_from, const Vector3 &p_to, MeshCollisionObject3D **p_results, int p_max_results, int *p_result_indices = nullptr);
	virtual int cull_aabb(const AABB &p_aabb, MeshCollisionObject3D **p_results, int p_max_results, int *p_result_indices = nullptr);

	virtual void set_pair_callback(PairCallback p_pair_callback, void *p_userdata);
	virtual void set_unpair_callback(UnpairCallback p_unpair_callback, void *p_userdata);

	virtual void update();

	static MeshBroadPhase3D *_create();
	MeshBroadPhase3DBVH();
};

#endif // MESH_BROAD_PHASE_3D_BVH_H
