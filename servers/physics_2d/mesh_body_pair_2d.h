/*************************************************************************/
/*  mesh_body_pair_2d.h                                                 */
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

#ifndef MESH_BODY_PAIR_2D_H
#define MESH_BODY_PAIR_2D_H

#include "mesh_body_2d.h"
#include "mesh_constraint_2d.h"

class MeshBodyPair2D : public MeshConstraint2D {
	enum {
		MAX_CONTACTS = 2
	};
	union {
		struct {
			MeshBody2D *A;
			MeshBody2D *B;
		};

		MeshBody2D *_arr[2] = { nullptr, nullptr };
	};

	int shape_A = 0;
	int shape_B = 0;

	bool collide_A = false;
	bool collide_B = false;

	MeshSpace2D *space = nullptr;

	struct Contact {
		Vector2 position;
		Vector2 normal;
		Vector2 local_A, local_B;
		real_t acc_normal_impulse = 0.0; // accumulated normal impulse (Pn)
		real_t acc_tangent_impulse = 0.0; // accumulated tangent impulse (Pt)
		real_t acc_bias_impulse = 0.0; // accumulated normal impulse for position bias (Pnb)
		real_t acc_bias_impulse_center_of_mass = 0.0; // accumulated normal impulse for position bias applied to com
		real_t mass_normal, mass_tangent = 0.0;
		real_t bias = 0.0;

		real_t depth = 0.0;
		bool active = false;
		bool used = false;
		Vector2 rA, rB;
		real_t bounce = 0.0;
	};

	Vector2 offset_B; //use local A coordinates to avoid numerical issues on collision detection

	Vector2 sep_axis;
	Contact contacts[MAX_CONTACTS];
	int contact_count = 0;
	bool collided = false;
	bool check_ccd = false;
	bool oneway_disabled = false;
	bool report_contacts_only = false;

	bool _test_ccd(real_t p_step, MeshBody2D *p_A, int p_shape_A, const Transform2D &p_xform_A, MeshBody2D *p_B, int p_shape_B, const Transform2D &p_xform_B);
	void _validate_contacts();
	static void _add_contact(const Vector2 &p_point_A, const Vector2 &p_point_B, void *p_self);
	_FORCE_INLINE_ void _contact_added_callback(const Vector2 &p_point_A, const Vector2 &p_point_B);

public:
	virtual bool setup(real_t p_step) override;
	virtual bool pre_solve(real_t p_step) override;
	virtual void solve(real_t p_step) override;

	MeshBodyPair2D(MeshBody2D *p_A, int p_shape_A, MeshBody2D *p_B, int p_shape_B);
	~MeshBodyPair2D();
};

#endif // MESH_BODY_PAIR_2D_H