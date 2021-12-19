/*************************************************************************/
/*  mesh_step_3d.h                                                      */
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

#ifndef MESH_STEP_3D_H
#define MESH_STEP_3D_H

#include "mesh_space_3d.h"

#include "core/templates/local_vector.h"
#include "core/templates/thread_work_pool.h"

class MeshStep3D {
	uint64_t _step = 1;

	int iterations = 0;
	real_t delta = 0.0;

	ThreadWorkPool work_pool;

	LocalVector<LocalVector<MeshBody3D *>> body_islands;
	LocalVector<LocalVector<MeshConstraint3D *>> constraint_islands;
	LocalVector<MeshConstraint3D *> all_constraints;

	void _populate_island(MeshBody3D *p_body, LocalVector<MeshBody3D *> &p_body_island, LocalVector<MeshConstraint3D *> &p_constraint_island);
	void _populate_island_soft_body(MeshSoftBody3D *p_soft_body, LocalVector<MeshBody3D *> &p_body_island, LocalVector<MeshConstraint3D *> &p_constraint_island);
	void _setup_contraint(uint32_t p_constraint_index, void *p_userdata = nullptr);
	void _pre_solve_island(LocalVector<MeshConstraint3D *> &p_constraint_island) const;
	void _solve_island(uint32_t p_island_index, void *p_userdata = nullptr);
	void _check_suspend(const LocalVector<MeshBody3D *> &p_body_island) const;

public:
	void step(MeshSpace3D *p_space, real_t p_delta);
	MeshStep3D();
	~MeshStep3D();
};

#endif // MESH_STEP_3D_H
