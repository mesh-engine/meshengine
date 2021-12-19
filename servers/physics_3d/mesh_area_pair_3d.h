/*************************************************************************/
/*  mesh_area_pair_3d.h                                                 */
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

#ifndef MESH_AREA_PAIR_3D_H
#define MESH_AREA_PAIR_3D_H

#include "mesh_area_3d.h"
#include "mesh_body_3d.h"
#include "mesh_constraint_3d.h"
#include "mesh_soft_body_3d.h"

class MeshAreaPair3D : public MeshConstraint3D {
	MeshBody3D *body;
	MeshArea3D *area;
	int body_shape;
	int area_shape;
	bool colliding = false;
	bool process_collision = false;
	bool has_space_override = false;

public:
	virtual bool setup(real_t p_step) override;
	virtual bool pre_solve(real_t p_step) override;
	virtual void solve(real_t p_step) override;

	MeshAreaPair3D(MeshBody3D *p_body, int p_body_shape, MeshArea3D *p_area, int p_area_shape);
	~MeshAreaPair3D();
};

class MeshArea2Pair3D : public MeshConstraint3D {
	MeshArea3D *area_a;
	MeshArea3D *area_b;
	int shape_a;
	int shape_b;
	bool colliding_a = false;
	bool colliding_b = false;
	bool process_collision_a = false;
	bool process_collision_b = false;
	bool area_a_monitorable;
	bool area_b_monitorable;

public:
	virtual bool setup(real_t p_step) override;
	virtual bool pre_solve(real_t p_step) override;
	virtual void solve(real_t p_step) override;

	MeshArea2Pair3D(MeshArea3D *p_area_a, int p_shape_a, MeshArea3D *p_area_b, int p_shape_b);
	~MeshArea2Pair3D();
};

class MeshAreaSoftBodyPair3D : public MeshConstraint3D {
	MeshSoftBody3D *soft_body;
	MeshArea3D *area;
	int soft_body_shape;
	int area_shape;
	bool colliding = false;
	bool process_collision = false;
	bool has_space_override = false;

public:
	virtual bool setup(real_t p_step) override;
	virtual bool pre_solve(real_t p_step) override;
	virtual void solve(real_t p_step) override;

	MeshAreaSoftBodyPair3D(MeshSoftBody3D *p_sof_body, int p_soft_body_shape, MeshArea3D *p_area, int p_area_shape);
	~MeshAreaSoftBodyPair3D();
};

#endif // MESH_AREA_PAIR_3D_H
