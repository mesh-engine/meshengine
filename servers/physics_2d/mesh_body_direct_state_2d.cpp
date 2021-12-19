/*************************************************************************/
/*  mesh_body_direct_state_2d.cpp                                       */
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

#include "mesh_body_direct_state_2d.h"

#include "mesh_body_2d.h"
#include "mesh_physics_server_2d.h"
#include "mesh_space_2d.h"

Vector2 MeshPhysicsDirectBodyState2D::get_total_gravity() const {
	return body->gravity;
}

real_t MeshPhysicsDirectBodyState2D::get_total_angular_damp() const {
	return body->total_angular_damp;
}

real_t MeshPhysicsDirectBodyState2D::get_total_linear_damp() const {
	return body->total_linear_damp;
}

Vector2 MeshPhysicsDirectBodyState2D::get_center_of_mass() const {
	return body->get_center_of_mass();
}

Vector2 MeshPhysicsDirectBodyState2D::get_center_of_mass_local() const {
	return body->get_center_of_mass_local();
}

real_t MeshPhysicsDirectBodyState2D::get_inverse_mass() const {
	return body->get_inv_mass();
}

real_t MeshPhysicsDirectBodyState2D::get_inverse_inertia() const {
	return body->get_inv_inertia();
}

void MeshPhysicsDirectBodyState2D::set_linear_velocity(const Vector2 &p_velocity) {
	body->wakeup();
	body->set_linear_velocity(p_velocity);
}

Vector2 MeshPhysicsDirectBodyState2D::get_linear_velocity() const {
	return body->get_linear_velocity();
}

void MeshPhysicsDirectBodyState2D::set_angular_velocity(real_t p_velocity) {
	body->wakeup();
	body->set_angular_velocity(p_velocity);
}

real_t MeshPhysicsDirectBodyState2D::get_angular_velocity() const {
	return body->get_angular_velocity();
}

void MeshPhysicsDirectBodyState2D::set_transform(const Transform2D &p_transform) {
	body->set_state(PhysicsServer2D::BODY_STATE_TRANSFORM, p_transform);
}

Transform2D MeshPhysicsDirectBodyState2D::get_transform() const {
	return body->get_transform();
}

Vector2 MeshPhysicsDirectBodyState2D::get_velocity_at_local_position(const Vector2 &p_position) const {
	return body->get_velocity_in_local_point(p_position);
}

void MeshPhysicsDirectBodyState2D::apply_central_impulse(const Vector2 &p_impulse) {
	body->wakeup();
	body->apply_central_impulse(p_impulse);
}

void MeshPhysicsDirectBodyState2D::apply_impulse(const Vector2 &p_impulse, const Vector2 &p_position) {
	body->wakeup();
	body->apply_impulse(p_impulse, p_position);
}

void MeshPhysicsDirectBodyState2D::apply_torque_impulse(real_t p_torque) {
	body->wakeup();
	body->apply_torque_impulse(p_torque);
}

void MeshPhysicsDirectBodyState2D::apply_central_force(const Vector2 &p_force) {
	body->wakeup();
	body->apply_central_force(p_force);
}

void MeshPhysicsDirectBodyState2D::apply_force(const Vector2 &p_force, const Vector2 &p_position) {
	body->wakeup();
	body->apply_force(p_force, p_position);
}

void MeshPhysicsDirectBodyState2D::apply_torque(real_t p_torque) {
	body->wakeup();
	body->apply_torque(p_torque);
}

void MeshPhysicsDirectBodyState2D::add_constant_central_force(const Vector2 &p_force) {
	body->wakeup();
	body->add_constant_central_force(p_force);
}

void MeshPhysicsDirectBodyState2D::add_constant_force(const Vector2 &p_force, const Vector2 &p_position) {
	body->wakeup();
	body->add_constant_force(p_force, p_position);
}

void MeshPhysicsDirectBodyState2D::add_constant_torque(real_t p_torque) {
	body->wakeup();
	body->add_constant_torque(p_torque);
}

void MeshPhysicsDirectBodyState2D::set_constant_force(const Vector2 &p_force) {
	if (!p_force.is_equal_approx(Vector2())) {
		body->wakeup();
	}
	body->set_constant_force(p_force);
}

Vector2 MeshPhysicsDirectBodyState2D::get_constant_force() const {
	return body->get_constant_force();
}

void MeshPhysicsDirectBodyState2D::set_constant_torque(real_t p_torque) {
	if (!Math::is_zero_approx(p_torque)) {
		body->wakeup();
	}
	body->set_constant_torque(p_torque);
}

real_t MeshPhysicsDirectBodyState2D::get_constant_torque() const {
	return body->get_constant_torque();
}

void MeshPhysicsDirectBodyState2D::set_sleep_state(bool p_enable) {
	body->set_active(!p_enable);
}

bool MeshPhysicsDirectBodyState2D::is_sleeping() const {
	return !body->is_active();
}

int MeshPhysicsDirectBodyState2D::get_contact_count() const {
	return body->contact_count;
}

Vector2 MeshPhysicsDirectBodyState2D::get_contact_local_position(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, Vector2());
	return body->contacts[p_contact_idx].local_pos;
}

Vector2 MeshPhysicsDirectBodyState2D::get_contact_local_normal(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, Vector2());
	return body->contacts[p_contact_idx].local_normal;
}

int MeshPhysicsDirectBodyState2D::get_contact_local_shape(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, -1);
	return body->contacts[p_contact_idx].local_shape;
}

RID MeshPhysicsDirectBodyState2D::get_contact_collider(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, RID());
	return body->contacts[p_contact_idx].collider;
}
Vector2 MeshPhysicsDirectBodyState2D::get_contact_collider_position(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, Vector2());
	return body->contacts[p_contact_idx].collider_pos;
}

ObjectID MeshPhysicsDirectBodyState2D::get_contact_collider_id(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, ObjectID());
	return body->contacts[p_contact_idx].collider_instance_id;
}

int MeshPhysicsDirectBodyState2D::get_contact_collider_shape(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, 0);
	return body->contacts[p_contact_idx].collider_shape;
}

Vector2 MeshPhysicsDirectBodyState2D::get_contact_collider_velocity_at_position(int p_contact_idx) const {
	ERR_FAIL_INDEX_V(p_contact_idx, body->contact_count, Vector2());
	return body->contacts[p_contact_idx].collider_velocity_at_pos;
}

PhysicsDirectSpaceState2D *MeshPhysicsDirectBodyState2D::get_space_state() {
	return body->get_space()->get_direct_state();
}

real_t MeshPhysicsDirectBodyState2D::get_step() const {
	return body->get_space()->get_last_step();
}
