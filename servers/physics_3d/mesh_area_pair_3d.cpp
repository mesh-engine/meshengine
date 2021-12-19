/*************************************************************************/
/*  mesh_area_pair_3d.cpp                                               */
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

#include "mesh_area_pair_3d.h"

#include "mesh_collision_solver_3d.h"

bool MeshAreaPair3D::setup(real_t p_step) {
	bool result = false;
	if (area->collides_with(body) && MeshCollisionSolver3D::solve_static(body->get_shape(body_shape), body->get_transform() * body->get_shape_transform(body_shape), area->get_shape(area_shape), area->get_transform() * area->get_shape_transform(area_shape), nullptr, this)) {
		result = true;
	}

	process_collision = false;
	has_space_override = false;
	if (result != colliding) {
		if ((int)area->get_param(PhysicsServer3D::AREA_PARAM_GRAVITY_OVERRIDE_MODE) != PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED) {
			has_space_override = true;
		} else if ((int)area->get_param(PhysicsServer3D::AREA_PARAM_LINEAR_DAMP_OVERRIDE_MODE) != PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED) {
			has_space_override = true;
		} else if ((int)area->get_param(PhysicsServer3D::AREA_PARAM_ANGULAR_DAMP_OVERRIDE_MODE) != PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED) {
			has_space_override = true;
		}
		process_collision = has_space_override;

		if (area->has_monitor_callback()) {
			process_collision = true;
		}

		colliding = result;
	}

	return process_collision;
}

bool MeshAreaPair3D::pre_solve(real_t p_step) {
	if (!process_collision) {
		return false;
	}

	if (colliding) {
		if (has_space_override) {
			body->add_area(area);
		}

		if (area->has_monitor_callback()) {
			area->add_body_to_query(body, body_shape, area_shape);
		}
	} else {
		if (has_space_override) {
			body->remove_area(area);
		}

		if (area->has_monitor_callback()) {
			area->remove_body_from_query(body, body_shape, area_shape);
		}
	}

	return false; // Never do any post solving.
}

void MeshAreaPair3D::solve(real_t p_step) {
	// Nothing to do.
}

MeshAreaPair3D::MeshAreaPair3D(MeshBody3D *p_body, int p_body_shape, MeshArea3D *p_area, int p_area_shape) {
	body = p_body;
	area = p_area;
	body_shape = p_body_shape;
	area_shape = p_area_shape;
	body->add_constraint(this, 0);
	area->add_constraint(this);
	if (p_body->get_mode() == PhysicsServer3D::BODY_MODE_KINEMATIC) {
		p_body->set_active(true);
	}
}

MeshAreaPair3D::~MeshAreaPair3D() {
	if (colliding) {
		if (has_space_override) {
			body->remove_area(area);
		}
		if (area->has_monitor_callback()) {
			area->remove_body_from_query(body, body_shape, area_shape);
		}
	}
	body->remove_constraint(this);
	area->remove_constraint(this);
}

////////////////////////////////////////////////////

bool MeshArea2Pair3D::setup(real_t p_step) {
	bool result_a = area_a->collides_with(area_b);
	bool result_b = area_b->collides_with(area_a);
	if ((result_a || result_b) && !MeshCollisionSolver3D::solve_static(area_a->get_shape(shape_a), area_a->get_transform() * area_a->get_shape_transform(shape_a), area_b->get_shape(shape_b), area_b->get_transform() * area_b->get_shape_transform(shape_b), nullptr, this)) {
		result_a = false;
		result_b = false;
	}

	bool process_collision = false;

	process_collision_a = false;
	if (result_a != colliding_a) {
		if (area_a->has_area_monitor_callback() && area_b_monitorable) {
			process_collision_a = true;
			process_collision = true;
		}
		colliding_a = result_a;
	}

	process_collision_b = false;
	if (result_b != colliding_b) {
		if (area_b->has_area_monitor_callback() && area_a_monitorable) {
			process_collision_b = true;
			process_collision = true;
		}
		colliding_b = result_b;
	}

	return process_collision;
}

bool MeshArea2Pair3D::pre_solve(real_t p_step) {
	if (process_collision_a) {
		if (colliding_a) {
			area_a->add_area_to_query(area_b, shape_b, shape_a);
		} else {
			area_a->remove_area_from_query(area_b, shape_b, shape_a);
		}
	}

	if (process_collision_b) {
		if (colliding_b) {
			area_b->add_area_to_query(area_a, shape_a, shape_b);
		} else {
			area_b->remove_area_from_query(area_a, shape_a, shape_b);
		}
	}

	return false; // Never do any post solving.
}

void MeshArea2Pair3D::solve(real_t p_step) {
	// Nothing to do.
}

MeshArea2Pair3D::MeshArea2Pair3D(MeshArea3D *p_area_a, int p_shape_a, MeshArea3D *p_area_b, int p_shape_b) {
	area_a = p_area_a;
	area_b = p_area_b;
	shape_a = p_shape_a;
	shape_b = p_shape_b;
	area_a_monitorable = area_a->is_monitorable();
	area_b_monitorable = area_b->is_monitorable();
	area_a->add_constraint(this);
	area_b->add_constraint(this);
}

MeshArea2Pair3D::~MeshArea2Pair3D() {
	if (colliding_a) {
		if (area_a->has_area_monitor_callback() && area_b_monitorable) {
			area_a->remove_area_from_query(area_b, shape_b, shape_a);
		}
	}

	if (colliding_b) {
		if (area_b->has_area_monitor_callback() && area_a_monitorable) {
			area_b->remove_area_from_query(area_a, shape_a, shape_b);
		}
	}

	area_a->remove_constraint(this);
	area_b->remove_constraint(this);
}

////////////////////////////////////////////////////

bool MeshAreaSoftBodyPair3D::setup(real_t p_step) {
	bool result = false;
	if (
			area->collides_with(soft_body) &&
			MeshCollisionSolver3D::solve_static(
					soft_body->get_shape(soft_body_shape),
					soft_body->get_transform() * soft_body->get_shape_transform(soft_body_shape),
					area->get_shape(area_shape),
					area->get_transform() * area->get_shape_transform(area_shape),
					nullptr,
					this)) {
		result = true;
	}

	process_collision = false;
	has_space_override = false;
	if (result != colliding) {
		if ((int)area->get_param(PhysicsServer3D::AREA_PARAM_GRAVITY_OVERRIDE_MODE) != PhysicsServer3D::AREA_SPACE_OVERRIDE_DISABLED) {
			has_space_override = true;
		} else if (area->get_wind_force_magnitude() > CMP_EPSILON) {
			has_space_override = true;
		}

		if (area->has_monitor_callback()) {
			process_collision = true;
		}

		colliding = result;
	}

	return process_collision;
}

bool MeshAreaSoftBodyPair3D::pre_solve(real_t p_step) {
	if (!process_collision) {
		return false;
	}

	if (colliding) {
		if (has_space_override) {
			soft_body->add_area(area);
		}

		if (area->has_monitor_callback()) {
			area->add_soft_body_to_query(soft_body, soft_body_shape, area_shape);
		}
	} else {
		if (has_space_override) {
			soft_body->remove_area(area);
		}

		if (area->has_monitor_callback()) {
			area->remove_soft_body_from_query(soft_body, soft_body_shape, area_shape);
		}
	}

	return false; // Never do any post solving.
}

void MeshAreaSoftBodyPair3D::solve(real_t p_step) {
	// Nothing to do.
}

MeshAreaSoftBodyPair3D::MeshAreaSoftBodyPair3D(MeshSoftBody3D *p_soft_body, int p_soft_body_shape, MeshArea3D *p_area, int p_area_shape) {
	soft_body = p_soft_body;
	area = p_area;
	soft_body_shape = p_soft_body_shape;
	area_shape = p_area_shape;
	soft_body->add_constraint(this);
	area->add_constraint(this);
}

MeshAreaSoftBodyPair3D::~MeshAreaSoftBodyPair3D() {
	if (colliding) {
		if (has_space_override) {
			soft_body->remove_area(area);
		}
		if (area->has_monitor_callback()) {
			area->remove_soft_body_from_query(soft_body, soft_body_shape, area_shape);
		}
	}
	soft_body->remove_constraint(this);
	area->remove_constraint(this);
}
