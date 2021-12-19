/*************************************************************************/
/*  variant.cpp                                                          */
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

#include "gdnative/variant.h"

#include "core/object/ref_counted.h"
#include "core/variant/variant.h"

#ifdef __cplusplus
extern "C" {
#endif

static_assert(sizeof(mesh_variant) == sizeof(Variant), "Variant size mismatch");

// Workaround GCC ICE on armv7hl which was affected GCC 6.0 up to 8.0 (GH-16100).
// It was fixed upstream in 8.1, and a fix was backported to 7.4.
// This can be removed once no supported distro ships with versions older than 7.4.
#if defined(__arm__) && defined(__GNUC__) && !defined(__clang__) && \
		(__GNUC__ == 6 || (__GNUC__ == 7 && __GNUC_MINOR__ < 4) || (__GNUC__ == 8 && __GNUC_MINOR__ < 1))
#pragma GCC push_options
#pragma GCC optimize("-O0")
#endif

#if defined(__arm__) && defined(__GNUC__) && !defined(__clang__) && \
		(__GNUC__ == 6 || (__GNUC__ == 7 && __GNUC_MINOR__ < 4) || (__GNUC__ == 8 && __GNUC_MINOR__ < 1))
#pragma GCC pop_options
#endif

// Memory

void GDAPI mesh_variant_new_copy(mesh_variant *p_dest, const mesh_variant *p_src) {
	Variant *dest = (Variant *)p_dest;
	const Variant *src = (const Variant *)p_src;
	memnew_placement(dest, Variant(*src));
}

void GDAPI mesh_variant_new_nil(mesh_variant *r_dest) {
	Variant *dest = (Variant *)r_dest;
	memnew_placement(dest, Variant);
}

void GDAPI mesh_variant_new_bool(mesh_variant *r_dest, const mesh_bool p_b) {
	Variant *dest = (Variant *)r_dest;
	memnew_placement(dest, Variant(p_b));
}

void GDAPI mesh_variant_new_int(mesh_variant *r_dest, const mesh_int p_i) {
	Variant *dest = (Variant *)r_dest;
	memnew_placement(dest, Variant(p_i));
}

void GDAPI mesh_variant_new_float(mesh_variant *r_dest, const mesh_float p_r) {
	Variant *dest = (Variant *)r_dest;
	memnew_placement(dest, Variant(p_r));
}

void GDAPI mesh_variant_new_string(mesh_variant *r_dest, const mesh_string *p_s) {
	Variant *dest = (Variant *)r_dest;
	const String *s = (const String *)p_s;
	memnew_placement(dest, Variant(*s));
}

void GDAPI mesh_variant_new_string_name(mesh_variant *r_dest, const mesh_string_name *p_s) {
	Variant *dest = (Variant *)r_dest;
	const StringName *s = (const StringName *)p_s;
	memnew_placement(dest, Variant(*s));
}

void GDAPI mesh_variant_new_vector2(mesh_variant *r_dest, const mesh_vector2 *p_v2) {
	Variant *dest = (Variant *)r_dest;
	const Vector2 *v2 = (const Vector2 *)p_v2;
	memnew_placement(dest, Variant(*v2));
}

void GDAPI mesh_variant_new_vector2i(mesh_variant *r_dest, const mesh_vector2i *p_v2) {
	Variant *dest = (Variant *)r_dest;
	const Vector2i *v2 = (const Vector2i *)p_v2;
	memnew_placement(dest, Variant(*v2));
}

void GDAPI mesh_variant_new_rect2(mesh_variant *r_dest, const mesh_rect2 *p_rect2) {
	Variant *dest = (Variant *)r_dest;
	const Rect2 *rect2 = (const Rect2 *)p_rect2;
	memnew_placement(dest, Variant(*rect2));
}

void GDAPI mesh_variant_new_rect2i(mesh_variant *r_dest, const mesh_rect2i *p_rect2) {
	Variant *dest = (Variant *)r_dest;
	const Rect2i *rect2 = (const Rect2i *)p_rect2;
	memnew_placement(dest, Variant(*rect2));
}

void GDAPI mesh_variant_new_vector3(mesh_variant *r_dest, const mesh_vector3 *p_v3) {
	Variant *dest = (Variant *)r_dest;
	const Vector3 *v3 = (const Vector3 *)p_v3;
	memnew_placement(dest, Variant(*v3));
}

void GDAPI mesh_variant_new_vector3i(mesh_variant *r_dest, const mesh_vector3i *p_v3) {
	Variant *dest = (Variant *)r_dest;
	const Vector3i *v3 = (const Vector3i *)p_v3;
	memnew_placement(dest, Variant(*v3));
}

void GDAPI mesh_variant_new_transform2d(mesh_variant *r_dest, const mesh_transform2d *p_t2d) {
	Variant *dest = (Variant *)r_dest;
	const Transform2D *t2d = (const Transform2D *)p_t2d;
	memnew_placement(dest, Variant(*t2d));
}

void GDAPI mesh_variant_new_plane(mesh_variant *r_dest, const mesh_plane *p_plane) {
	Variant *dest = (Variant *)r_dest;
	const Plane *plane = (const Plane *)p_plane;
	memnew_placement(dest, Variant(*plane));
}

void GDAPI mesh_variant_new_quaternion(mesh_variant *r_dest, const mesh_quaternion *p_quaternion) {
	Variant *dest = (Variant *)r_dest;
	const Quaternion *quaternion = (const Quaternion *)p_quaternion;
	memnew_placement(dest, Variant(*quaternion));
}

void GDAPI mesh_variant_new_aabb(mesh_variant *r_dest, const mesh_aabb *p_aabb) {
	Variant *dest = (Variant *)r_dest;
	const AABB *aabb = (const AABB *)p_aabb;
	memnew_placement(dest, Variant(*aabb));
}

void GDAPI mesh_variant_new_basis(mesh_variant *r_dest, const mesh_basis *p_basis) {
	Variant *dest = (Variant *)r_dest;
	const Basis *basis = (const Basis *)p_basis;
	memnew_placement(dest, Variant(*basis));
}

void GDAPI mesh_variant_new_transform3d(mesh_variant *r_dest, const mesh_transform3d *p_trans) {
	Variant *dest = (Variant *)r_dest;
	const Transform3D *trans = (const Transform3D *)p_trans;
	memnew_placement(dest, Variant(*trans));
}

void GDAPI mesh_variant_new_color(mesh_variant *r_dest, const mesh_color *p_color) {
	Variant *dest = (Variant *)r_dest;
	const Color *color = (const Color *)p_color;
	memnew_placement(dest, Variant(*color));
}

void GDAPI mesh_variant_new_node_path(mesh_variant *r_dest, const mesh_node_path *p_np) {
	Variant *dest = (Variant *)r_dest;
	const NodePath *np = (const NodePath *)p_np;
	memnew_placement(dest, Variant(*np));
}

void GDAPI mesh_variant_new_rid(mesh_variant *r_dest, const mesh_rid *p_rid) {
	Variant *dest = (Variant *)r_dest;
	const RID *rid = (const RID *)p_rid;
	memnew_placement(dest, Variant(*rid));
}

void GDAPI mesh_variant_new_callable(mesh_variant *r_dest, const mesh_callable *p_cb) {
	Variant *dest = (Variant *)r_dest;
	const Callable *cb = (const Callable *)p_cb;
	memnew_placement(dest, Variant(*cb));
}

void GDAPI mesh_variant_new_signal(mesh_variant *r_dest, const mesh_signal *p_signal) {
	Variant *dest = (Variant *)r_dest;
	const Signal *signal = (const Signal *)p_signal;
	memnew_placement(dest, Variant(*signal));
}

void GDAPI mesh_variant_new_object(mesh_variant *r_dest, const mesh_object *p_obj) {
	Variant *dest = (Variant *)r_dest;
	const Object *obj = (const Object *)p_obj;
	const RefCounted *ref_counted = Object::cast_to<RefCounted>(obj);
	REF ref;
	if (ref_counted) {
		ref = REF(ref_counted);
	}
	if (!ref.is_null()) {
		memnew_placement(dest, Variant(ref));
	} else {
#if defined(DEBUG_METHODS_ENABLED)
		if (ref_counted) {
			ERR_PRINT("RefCounted object has 0 refcount in mesh_variant_new_object - you lost it somewhere.");
		}
#endif
		memnew_placement(dest, Variant(obj));
	}
}

void GDAPI mesh_variant_new_dictionary(mesh_variant *r_dest, const mesh_dictionary *p_dict) {
	Variant *dest = (Variant *)r_dest;
	const Dictionary *dict = (const Dictionary *)p_dict;
	memnew_placement(dest, Variant(*dict));
}

void GDAPI mesh_variant_new_array(mesh_variant *r_dest, const mesh_array *p_arr) {
	Variant *dest = (Variant *)r_dest;
	const Array *arr = (const Array *)p_arr;
	memnew_placement(dest, Variant(*arr));
}

void GDAPI mesh_variant_new_packed_byte_array(mesh_variant *r_dest, const mesh_packed_byte_array *p_pba) {
	Variant *dest = (Variant *)r_dest;
	const PackedByteArray *pba = (const PackedByteArray *)p_pba;
	memnew_placement(dest, Variant(*pba));
}

void GDAPI mesh_variant_new_packed_int32_array(mesh_variant *r_dest, const mesh_packed_int32_array *p_pia) {
	Variant *dest = (Variant *)r_dest;
	const PackedInt32Array *pia = (const PackedInt32Array *)p_pia;
	memnew_placement(dest, Variant(*pia));
}

void GDAPI mesh_variant_new_packed_int64_array(mesh_variant *r_dest, const mesh_packed_int64_array *p_pia) {
	Variant *dest = (Variant *)r_dest;
	const PackedInt64Array *pia = (const PackedInt64Array *)p_pia;
	memnew_placement(dest, Variant(*pia));
}

void GDAPI mesh_variant_new_packed_float32_array(mesh_variant *r_dest, const mesh_packed_float32_array *p_pra) {
	Variant *dest = (Variant *)r_dest;
	const PackedFloat32Array *pra = (const PackedFloat32Array *)p_pra;
	memnew_placement(dest, Variant(*pra));
}

void GDAPI mesh_variant_new_packed_float64_array(mesh_variant *r_dest, const mesh_packed_float64_array *p_pra) {
	Variant *dest = (Variant *)r_dest;
	const PackedFloat64Array *pra = (const PackedFloat64Array *)p_pra;
	memnew_placement(dest, Variant(*pra));
}

void GDAPI mesh_variant_new_packed_string_array(mesh_variant *r_dest, const mesh_packed_string_array *p_psa) {
	Variant *dest = (Variant *)r_dest;
	const PackedStringArray *psa = (const PackedStringArray *)p_psa;
	memnew_placement(dest, Variant(*psa));
}

void GDAPI mesh_variant_new_packed_vector2_array(mesh_variant *r_dest, const mesh_packed_vector2_array *p_pv2a) {
	Variant *dest = (Variant *)r_dest;
	const PackedVector2Array *pv2a = (const PackedVector2Array *)p_pv2a;
	memnew_placement(dest, Variant(*pv2a));
}

void GDAPI mesh_variant_new_packed_vector3_array(mesh_variant *r_dest, const mesh_packed_vector3_array *p_pv3a) {
	Variant *dest = (Variant *)r_dest;
	const PackedVector3Array *pv3a = (const PackedVector3Array *)p_pv3a;
	memnew_placement(dest, Variant(*pv3a));
}

void GDAPI mesh_variant_new_packed_color_array(mesh_variant *r_dest, const mesh_packed_color_array *p_pca) {
	Variant *dest = (Variant *)r_dest;
	const PackedColorArray *pca = (const PackedColorArray *)p_pca;
	memnew_placement(dest, Variant(*pca));
}

mesh_bool GDAPI mesh_variant_as_bool(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	return self->operator bool();
}

mesh_int GDAPI mesh_variant_as_int(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	return self->operator int64_t();
}

mesh_float GDAPI mesh_variant_as_float(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	return self->operator double();
}

mesh_string GDAPI mesh_variant_as_string(const mesh_variant *p_self) {
	mesh_string raw_dest;
	const Variant *self = (const Variant *)p_self;
	String *dest = (String *)&raw_dest;
	memnew_placement(dest, String(self->operator String())); // operator = is overloaded by String
	return raw_dest;
}

mesh_string_name GDAPI mesh_variant_as_string_name(const mesh_variant *p_self) {
	mesh_string_name raw_dest;
	const Variant *self = (const Variant *)p_self;
	StringName *dest = (StringName *)&raw_dest;
	memnew_placement(dest, StringName(self->operator StringName())); // operator = is overloaded by StringName
	return raw_dest;
}

mesh_vector2 GDAPI mesh_variant_as_vector2(const mesh_variant *p_self) {
	mesh_vector2 raw_dest;
	const Variant *self = (const Variant *)p_self;
	Vector2 *dest = (Vector2 *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_vector2i GDAPI mesh_variant_as_vector2i(const mesh_variant *p_self) {
	mesh_vector2i raw_dest;
	const Variant *self = (const Variant *)p_self;
	Vector2i *dest = (Vector2i *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_rect2 GDAPI mesh_variant_as_rect2(const mesh_variant *p_self) {
	mesh_rect2 raw_dest;
	const Variant *self = (const Variant *)p_self;
	Rect2 *dest = (Rect2 *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_rect2i GDAPI mesh_variant_as_rect2i(const mesh_variant *p_self) {
	mesh_rect2i raw_dest;
	const Variant *self = (const Variant *)p_self;
	Rect2i *dest = (Rect2i *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_vector3 GDAPI mesh_variant_as_vector3(const mesh_variant *p_self) {
	mesh_vector3 raw_dest;
	const Variant *self = (const Variant *)p_self;
	Vector3 *dest = (Vector3 *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_vector3i GDAPI mesh_variant_as_vector3i(const mesh_variant *p_self) {
	mesh_vector3i raw_dest;
	const Variant *self = (const Variant *)p_self;
	Vector3i *dest = (Vector3i *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_transform2d GDAPI mesh_variant_as_transform2d(const mesh_variant *p_self) {
	mesh_transform2d raw_dest;
	const Variant *self = (const Variant *)p_self;
	Transform2D *dest = (Transform2D *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_plane GDAPI mesh_variant_as_plane(const mesh_variant *p_self) {
	mesh_plane raw_dest;
	const Variant *self = (const Variant *)p_self;
	Plane *dest = (Plane *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_quaternion GDAPI mesh_variant_as_quaternion(const mesh_variant *p_self) {
	mesh_quaternion raw_dest;
	const Variant *self = (const Variant *)p_self;
	Quaternion *dest = (Quaternion *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_aabb GDAPI mesh_variant_as_aabb(const mesh_variant *p_self) {
	mesh_aabb raw_dest;
	const Variant *self = (const Variant *)p_self;
	AABB *dest = (AABB *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_basis GDAPI mesh_variant_as_basis(const mesh_variant *p_self) {
	mesh_basis raw_dest;
	const Variant *self = (const Variant *)p_self;
	Basis *dest = (Basis *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_transform3d GDAPI mesh_variant_as_transform3d(const mesh_variant *p_self) {
	mesh_transform3d raw_dest;
	const Variant *self = (const Variant *)p_self;
	Transform3D *dest = (Transform3D *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_color GDAPI mesh_variant_as_color(const mesh_variant *p_self) {
	mesh_color raw_dest;
	const Variant *self = (const Variant *)p_self;
	Color *dest = (Color *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_node_path GDAPI mesh_variant_as_node_path(const mesh_variant *p_self) {
	mesh_node_path raw_dest;
	const Variant *self = (const Variant *)p_self;
	NodePath *dest = (NodePath *)&raw_dest;
	memnew_placement(dest, NodePath(self->operator NodePath())); // operator = is overloaded by NodePath
	return raw_dest;
}

mesh_rid GDAPI mesh_variant_as_rid(const mesh_variant *p_self) {
	mesh_rid raw_dest;
	const Variant *self = (const Variant *)p_self;
	RID *dest = (RID *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_callable GDAPI mesh_variant_as_callable(const mesh_variant *p_self) {
	mesh_callable raw_dest;
	const Variant *self = (const Variant *)p_self;
	Callable *dest = (Callable *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_signal GDAPI mesh_variant_as_signal(const mesh_variant *p_self) {
	mesh_signal raw_dest;
	const Variant *self = (const Variant *)p_self;
	Signal *dest = (Signal *)&raw_dest;
	*dest = *self;
	return raw_dest;
}

mesh_object GDAPI *mesh_variant_as_object(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	Object *dest;
	dest = *self;
	return (mesh_object *)dest;
}

mesh_dictionary GDAPI mesh_variant_as_dictionary(const mesh_variant *p_self) {
	mesh_dictionary raw_dest;
	const Variant *self = (const Variant *)p_self;
	Dictionary *dest = (Dictionary *)&raw_dest;
	memnew_placement(dest, Dictionary(self->operator Dictionary())); // operator = is overloaded by Dictionary
	return raw_dest;
}

mesh_array GDAPI mesh_variant_as_array(const mesh_variant *p_self) {
	mesh_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	Array *dest = (Array *)&raw_dest;
	memnew_placement(dest, Array(self->operator Array())); // operator = is overloaded by Array
	return raw_dest;
}

mesh_packed_byte_array GDAPI mesh_variant_as_packed_byte_array(const mesh_variant *p_self) {
	mesh_packed_byte_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedByteArray *dest = (PackedByteArray *)&raw_dest;
	memnew_placement(dest, PackedByteArray(self->operator PackedByteArray())); // operator = is overloaded by PackedByteArray
	*dest = *self;
	return raw_dest;
}

mesh_packed_int32_array GDAPI mesh_variant_as_packed_int32_array(const mesh_variant *p_self) {
	mesh_packed_int32_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedInt32Array *dest = (PackedInt32Array *)&raw_dest;
	memnew_placement(dest, PackedInt32Array(self->operator PackedInt32Array())); // operator = is overloaded by PackedInt32Array
	*dest = *self;
	return raw_dest;
}

mesh_packed_int64_array GDAPI mesh_variant_as_packed_int64_array(const mesh_variant *p_self) {
	mesh_packed_int64_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedInt64Array *dest = (PackedInt64Array *)&raw_dest;
	memnew_placement(dest, PackedInt64Array(self->operator PackedInt64Array())); // operator = is overloaded by PackedInt64Array
	*dest = *self;
	return raw_dest;
}

mesh_packed_float32_array GDAPI mesh_variant_as_packed_float32_array(const mesh_variant *p_self) {
	mesh_packed_float32_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedFloat32Array *dest = (PackedFloat32Array *)&raw_dest;
	memnew_placement(dest, PackedFloat32Array(self->operator PackedFloat32Array())); // operator = is overloaded by PackedFloat32Array
	*dest = *self;
	return raw_dest;
}

mesh_packed_float64_array GDAPI mesh_variant_as_packed_float64_array(const mesh_variant *p_self) {
	mesh_packed_float64_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedFloat64Array *dest = (PackedFloat64Array *)&raw_dest;
	memnew_placement(dest, PackedFloat64Array(self->operator PackedFloat64Array())); // operator = is overloaded by PackedFloat64Array
	*dest = *self;
	return raw_dest;
}

mesh_packed_string_array GDAPI mesh_variant_as_packed_string_array(const mesh_variant *p_self) {
	mesh_packed_string_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedStringArray *dest = (PackedStringArray *)&raw_dest;
	memnew_placement(dest, PackedStringArray(self->operator PackedStringArray())); // operator = is overloaded by PackedStringArray
	*dest = *self;
	return raw_dest;
}

mesh_packed_vector2_array GDAPI mesh_variant_as_packed_vector2_array(const mesh_variant *p_self) {
	mesh_packed_vector2_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedVector2Array *dest = (PackedVector2Array *)&raw_dest;
	memnew_placement(dest, PackedVector2Array(self->operator PackedVector2Array())); // operator = is overloaded by PackedVector2Array
	*dest = *self;
	return raw_dest;
}

mesh_packed_vector3_array GDAPI mesh_variant_as_packed_vector3_array(const mesh_variant *p_self) {
	mesh_packed_vector3_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedVector3Array *dest = (PackedVector3Array *)&raw_dest;
	memnew_placement(dest, PackedVector3Array(self->operator PackedVector3Array())); // operator = is overloaded by PackedVector3Array
	*dest = *self;
	return raw_dest;
}

mesh_packed_color_array GDAPI mesh_variant_as_packed_color_array(const mesh_variant *p_self) {
	mesh_packed_color_array raw_dest;
	const Variant *self = (const Variant *)p_self;
	PackedColorArray *dest = (PackedColorArray *)&raw_dest;
	memnew_placement(dest, PackedColorArray(self->operator PackedColorArray())); // operator = is overloaded by PackedColorArray
	*dest = *self;
	return raw_dest;
}

void GDAPI mesh_variant_destroy(mesh_variant *p_self) {
	Variant *self = (Variant *)p_self;
	self->~Variant();
}

// Dynamic interaction.

void GDAPI mesh_variant_call(mesh_variant *p_self, const mesh_string_name *p_method, const mesh_variant **p_args, const mesh_int p_argcount, mesh_variant *r_return, mesh_variant_call_error *r_error) {
	Variant *self = (Variant *)p_self;
	const StringName *method = (const StringName *)p_method;
	const Variant **args = (const Variant **)p_args;
	Variant ret;
	Callable::CallError error;
	self->call(*method, args, p_argcount, ret, error);
	memnew_placement(r_return, Variant(ret));

	if (r_error) {
		r_error->error = (mesh_variant_call_error_error)error.error;
		r_error->argument = error.argument;
		r_error->expected = (mesh_variant_type)error.expected;
	}
}

void GDAPI mesh_variant_call_with_cstring(mesh_variant *p_self, const char *p_method, const mesh_variant **p_args, const mesh_int p_argcount, mesh_variant *r_return, mesh_variant_call_error *r_error) {
	Variant *self = (Variant *)p_self;
	const StringName method(p_method);
	const Variant **args = (const Variant **)p_args;
	Variant ret;
	Callable::CallError error;
	self->call(method, args, p_argcount, ret, error);
	memnew_placement(r_return, Variant(ret));

	if (r_error) {
		r_error->error = (mesh_variant_call_error_error)error.error;
		r_error->argument = error.argument;
		r_error->expected = (mesh_variant_type)error.expected;
	}
}

void GDAPI mesh_variant_call_static(mesh_variant_type p_type, const mesh_string_name *p_method, const mesh_variant **p_args, const mesh_int p_argcount, mesh_variant *r_return, mesh_variant_call_error *r_error) {
	Variant::Type type = (Variant::Type)p_type;
	const StringName *method = (const StringName *)p_method;
	const Variant **args = (const Variant **)p_args;
	Variant ret;
	Callable::CallError error;
	Variant::call_static(type, *method, args, p_argcount, ret, error);
	memnew_placement(r_return, Variant(ret));

	if (r_error) {
		r_error->error = (mesh_variant_call_error_error)error.error;
		r_error->argument = error.argument;
		r_error->expected = (mesh_variant_type)error.expected;
	}
}

void GDAPI mesh_variant_call_static_with_cstring(mesh_variant_type p_type, const char *p_method, const mesh_variant **p_args, const mesh_int p_argcount, mesh_variant *r_return, mesh_variant_call_error *r_error) {
	Variant::Type type = (Variant::Type)p_type;
	const StringName method(p_method);
	const Variant **args = (const Variant **)p_args;
	Variant ret;
	Callable::CallError error;
	Variant::call_static(type, method, args, p_argcount, ret, error);
	memnew_placement(r_return, Variant(ret));

	if (r_error) {
		r_error->error = (mesh_variant_call_error_error)error.error;
		r_error->argument = error.argument;
		r_error->expected = (mesh_variant_type)error.expected;
	}
}

void GDAPI mesh_variant_evaluate(mesh_variant_operator p_op, const mesh_variant *p_a, const mesh_variant *p_b, mesh_variant *r_return, bool *r_valid) {
	Variant::Operator op = (Variant::Operator)p_op;
	const Variant *a = (const Variant *)p_a;
	const Variant *b = (const Variant *)p_b;
	Variant *ret = (Variant *)r_return;
	Variant::evaluate(op, *a, *b, *ret, *r_valid);
}

void GDAPI mesh_variant_set(mesh_variant *p_self, const mesh_variant *p_key, const mesh_variant *p_value, bool *r_valid) {
	Variant *self = (Variant *)p_self;
	const Variant *key = (const Variant *)p_key;
	const Variant *value = (const Variant *)p_value;

	self->set(*key, *value, r_valid);
}

void GDAPI mesh_variant_set_named(mesh_variant *p_self, const mesh_string_name *p_key, const mesh_variant *p_value, bool *r_valid) {
	Variant *self = (Variant *)p_self;
	const StringName *key = (const StringName *)p_key;
	const Variant *value = (const Variant *)p_value;

	self->set_named(*key, *value, *r_valid);
}

void GDAPI mesh_variant_set_named_with_cstring(mesh_variant *p_self, const char *p_key, const mesh_variant *p_value, bool *r_valid) {
	Variant *self = (Variant *)p_self;
	const StringName key(p_key);
	const Variant *value = (const Variant *)p_value;

	self->set_named(key, *value, *r_valid);
}

void GDAPI mesh_variant_set_keyed(mesh_variant *p_self, const mesh_variant *p_key, const mesh_variant *p_value, bool *r_valid) {
	Variant *self = (Variant *)p_self;
	const Variant *key = (const Variant *)p_key;
	const Variant *value = (const Variant *)p_value;

	self->set_keyed(*key, *value, *r_valid);
}

void GDAPI mesh_variant_set_indexed(mesh_variant *p_self, mesh_int p_index, const mesh_variant *p_value, bool *r_valid, bool *r_oob) {
	Variant *self = (Variant *)p_self;
	const Variant *value = (const Variant *)p_value;

	self->set_indexed(p_index, value, *r_valid, *r_oob);
}

mesh_variant GDAPI mesh_variant_get(const mesh_variant *p_self, const mesh_variant *p_key, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	const Variant *key = (const Variant *)p_key;
	Variant ret;

	ret = self->get(*key, r_valid);
	mesh_variant result;
	memnew_placement(&result, Variant(ret));
	return result;
}

mesh_variant GDAPI mesh_variant_get_named(const mesh_variant *p_self, const mesh_string_name *p_key, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	const StringName *key = (const StringName *)p_key;
	Variant ret;

	ret = self->get_named(*key, *r_valid);
	mesh_variant result;
	memnew_placement(&result, Variant(ret));
	return result;
}

mesh_variant GDAPI mesh_variant_get_named_with_cstring(const mesh_variant *p_self, const char *p_key, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	const StringName *key = (const StringName *)p_key;
	Variant ret;

	ret = self->get_named(*key, *r_valid);
	mesh_variant result;
	memnew_placement(&result, Variant(ret));
	return result;
}

mesh_variant GDAPI mesh_variant_get_keyed(const mesh_variant *p_self, const mesh_variant *p_key, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	const Variant *key = (const Variant *)p_key;
	Variant ret;

	ret = self->get_keyed(*key, *r_valid);
	mesh_variant result;
	memnew_placement(&result, Variant(ret));
	return result;
}

mesh_variant GDAPI mesh_variant_get_indexed(const mesh_variant *p_self, mesh_int p_index, bool *r_valid, bool *r_oob) {
	const Variant *self = (const Variant *)p_self;
	Variant ret;

	ret = self->get_indexed(p_index, *r_valid, *r_oob);
	mesh_variant result;
	memnew_placement(&result, Variant(ret));
	return result;
}

/// Iteration.
bool GDAPI mesh_variant_iter_init(const mesh_variant *p_self, mesh_variant *r_iter, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	Variant *iter = (Variant *)r_iter;

	return self->iter_init(*iter, *r_valid);
}

bool GDAPI mesh_variant_iter_next(const mesh_variant *p_self, mesh_variant *r_iter, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	Variant *iter = (Variant *)r_iter;

	return self->iter_next(*iter, *r_valid);
}

mesh_variant GDAPI mesh_variant_iter_get(const mesh_variant *p_self, mesh_variant *r_iter, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	Variant *iter = (Variant *)r_iter;

	Variant result = self->iter_next(*iter, *r_valid);
	mesh_variant ret;
	memnew_placement(&ret, Variant(result));
	return ret;
}

/// Variant functions.
mesh_bool GDAPI mesh_variant_hash_compare(const mesh_variant *p_self, const mesh_variant *p_other) {
	const Variant *self = (const Variant *)p_self;
	const Variant *other = (const Variant *)p_other;
	return self->hash_compare(*other);
}

mesh_bool GDAPI mesh_variant_booleanize(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	return self->booleanize();
}

void GDAPI mesh_variant_blend(const mesh_variant *p_a, const mesh_variant *p_b, float p_c, mesh_variant *r_dst) {
	const Variant *a = (const Variant *)p_a;
	const Variant *b = (const Variant *)p_b;
	Variant *dst = (Variant *)r_dst;
	Variant::blend(*a, *b, p_c, *dst);
}

void GDAPI mesh_variant_interpolate(const mesh_variant *p_a, const mesh_variant *p_b, float p_c, mesh_variant *r_dst) {
	const Variant *a = (const Variant *)p_a;
	const Variant *b = (const Variant *)p_b;
	Variant *dst = (Variant *)r_dst;
	Variant::interpolate(*a, *b, p_c, *dst);
}

mesh_variant GDAPI mesh_variant_duplicate(const mesh_variant *p_self, mesh_bool p_deep) {
	const Variant *self = (const Variant *)p_self;
	Variant result = self->duplicate(p_deep);
	mesh_variant ret;
	memnew_placement(&ret, Variant(result));
	return ret;
}

mesh_string GDAPI mesh_variant_stringify(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	String result = *self;
	mesh_string ret;
	memnew_placement(&ret, String(result));
	return ret;
}

// Discovery API

/// Operators
mesh_validated_operator_evaluator GDAPI mesh_variant_get_validated_operator_evaluator(mesh_variant_operator p_operator, mesh_variant_type p_type_a, mesh_variant_type p_type_b) {
	return (mesh_validated_operator_evaluator)Variant::get_validated_operator_evaluator((Variant::Operator)p_operator, (Variant::Type)p_type_a, (Variant::Type)p_type_b);
}

mesh_ptr_operator_evaluator GDAPI mesh_variant_get_ptr_operator_evaluator(mesh_variant_operator p_operator, mesh_variant_type p_type_a, mesh_variant_type p_type_b) {
	return (mesh_ptr_operator_evaluator)Variant::get_ptr_operator_evaluator((Variant::Operator)p_operator, (Variant::Type)p_type_a, (Variant::Type)p_type_b);
}

mesh_variant_type GDAPI mesh_variant_get_operator_return_type(mesh_variant_operator p_operator, mesh_variant_type p_type_a, mesh_variant_type p_type_b) {
	return (mesh_variant_type)Variant::get_operator_return_type((Variant::Operator)p_operator, (Variant::Type)p_type_a, (Variant::Type)p_type_b);
}

mesh_string GDAPI mesh_variant_get_operator_name(mesh_variant_operator p_operator) {
	String op_name = Variant::get_operator_name((Variant::Operator)p_operator);
	mesh_string ret;
	memnew_placement(&ret, String(op_name));
	return ret;
}

/// Built-in Methods

bool GDAPI mesh_variant_has_builtin_method(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return Variant::has_builtin_method((Variant::Type)p_type, *((const StringName *)p_method));
}

bool GDAPI mesh_variant_has_builtin_method_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return Variant::has_builtin_method((Variant::Type)p_type, StringName(p_method));
}

mesh_validated_builtin_method GDAPI mesh_variant_get_validated_builtin_method(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return (mesh_validated_builtin_method)Variant::get_validated_builtin_method((Variant::Type)p_type, *((const StringName *)p_method));
}

mesh_validated_builtin_method GDAPI mesh_variant_get_validated_builtin_method_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return (mesh_validated_builtin_method)Variant::get_validated_builtin_method((Variant::Type)p_type, StringName(p_method));
}

mesh_ptr_builtin_method GDAPI mesh_variant_get_ptr_builtin_method(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return (mesh_ptr_builtin_method)Variant::get_ptr_builtin_method((Variant::Type)p_type, *((const StringName *)p_method));
}

mesh_ptr_builtin_method GDAPI mesh_variant_get_ptr_builtin_method_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return (mesh_ptr_builtin_method)Variant::get_ptr_builtin_method((Variant::Type)p_type, StringName(p_method));
}

int GDAPI mesh_variant_get_builtin_method_argument_count(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return Variant::get_builtin_method_argument_count((Variant::Type)p_type, *((const StringName *)p_method));
}

int GDAPI mesh_variant_get_builtin_method_argument_count_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return Variant::get_builtin_method_argument_count((Variant::Type)p_type, StringName(p_method));
}

mesh_variant_type GDAPI mesh_variant_get_builtin_method_argument_type(mesh_variant_type p_type, const mesh_string_name *p_method, int p_argument) {
	return (mesh_variant_type)Variant::get_builtin_method_argument_type((Variant::Type)p_type, *((const StringName *)p_method), p_argument);
}

mesh_variant_type GDAPI mesh_variant_get_builtin_method_argument_type_with_cstring(mesh_variant_type p_type, const char *p_method, int p_argument) {
	return (mesh_variant_type)Variant::get_builtin_method_argument_type((Variant::Type)p_type, StringName(p_method), p_argument);
}

mesh_string GDAPI mesh_variant_get_builtin_method_argument_name(mesh_variant_type p_type, const mesh_string_name *p_method, int p_argument) {
	String name = Variant::get_builtin_method_argument_name((Variant::Type)p_type, *((const StringName *)p_method), p_argument);
	return *(mesh_string *)&name;
}

mesh_string GDAPI mesh_variant_get_builtin_method_argument_name_with_cstring(mesh_variant_type p_type, const char *p_method, int p_argument) {
	String name = Variant::get_builtin_method_argument_name((Variant::Type)p_type, StringName(p_method), p_argument);
	return *(mesh_string *)&name;
}

bool GDAPI mesh_variant_has_builtin_method_return_value(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return Variant::has_builtin_method_return_value((Variant::Type)p_type, *((const StringName *)p_method));
}

bool GDAPI mesh_variant_has_builtin_method_return_value_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return Variant::has_builtin_method_return_value((Variant::Type)p_type, StringName(p_method));
}

mesh_variant_type GDAPI mesh_variant_get_builtin_method_return_type(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return (mesh_variant_type)Variant::get_builtin_method_return_type((Variant::Type)p_type, *((const StringName *)p_method));
}

mesh_variant_type GDAPI mesh_variant_get_builtin_method_return_type_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return (mesh_variant_type)Variant::get_builtin_method_return_type((Variant::Type)p_type, StringName(p_method));
}

bool GDAPI mesh_variant_is_builtin_method_const(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return Variant::is_builtin_method_const((Variant::Type)p_type, *((const StringName *)p_method));
}

bool GDAPI mesh_variant_is_builtin_method_const_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return Variant::is_builtin_method_const((Variant::Type)p_type, StringName(p_method));
}

bool GDAPI mesh_variant_is_builtin_method_static(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return Variant::is_builtin_method_static((Variant::Type)p_type, *((const StringName *)p_method));
}

bool GDAPI mesh_variant_is_builtin_method_static_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return Variant::is_builtin_method_static((Variant::Type)p_type, StringName(p_method));
}

bool GDAPI mesh_variant_is_builtin_method_vararg(mesh_variant_type p_type, const mesh_string_name *p_method) {
	return Variant::is_builtin_method_vararg((Variant::Type)p_type, *((const StringName *)p_method));
}

bool GDAPI mesh_variant_is_builtin_method_vararg_with_cstring(mesh_variant_type p_type, const char *p_method) {
	return Variant::is_builtin_method_vararg((Variant::Type)p_type, StringName(p_method));
}

int GDAPI mesh_variant_get_builtin_method_count(mesh_variant_type p_type) {
	return Variant::get_builtin_method_count((Variant::Type)p_type);
}

void GDAPI mesh_variant_get_builtin_method_list(mesh_variant_type p_type, mesh_string_name *r_list) {
	List<StringName> list;
	Variant::get_builtin_method_list((Variant::Type)p_type, &list);
	int i = 0;
	for (const StringName &E : list) {
		memnew_placement(&r_list[i], StringName(E));
	}
}

/// Constructors

int GDAPI mesh_variant_get_constructor_count(mesh_variant_type p_type) {
	return Variant::get_constructor_count((Variant::Type)p_type);
}

mesh_validated_constructor GDAPI mesh_variant_get_validated_constructor(mesh_variant_type p_type, int p_constructor) {
	return (mesh_validated_constructor)Variant::get_validated_constructor((Variant::Type)p_type, p_constructor);
}

mesh_ptr_constructor GDAPI mesh_variant_get_ptr_constructor(mesh_variant_type p_type, int p_constructor) {
	return (mesh_ptr_constructor)Variant::get_ptr_constructor((Variant::Type)p_type, p_constructor);
}

int GDAPI mesh_variant_get_constructor_argument_count(mesh_variant_type p_type, int p_constructor) {
	return Variant::get_constructor_argument_count((Variant::Type)p_type, p_constructor);
}

mesh_variant_type GDAPI mesh_variant_get_constructor_argument_type(mesh_variant_type p_type, int p_constructor, int p_argument) {
	return (mesh_variant_type)Variant::get_constructor_argument_type((Variant::Type)p_type, p_constructor, p_argument);
}

mesh_string GDAPI mesh_variant_get_constructor_argument_name(mesh_variant_type p_type, int p_constructor, int p_argument) {
	String name = Variant::get_constructor_argument_name((Variant::Type)p_type, p_constructor, p_argument);
	mesh_string ret;
	memnew_placement(&ret, String(name));
	return ret;
}

void GDAPI mesh_variant_construct(mesh_variant_type p_type, mesh_variant *p_base, const mesh_variant **p_args, int p_argcount, mesh_variant_call_error *r_error) {
	Variant::construct((Variant::Type)p_type, *((Variant *)p_base), (const Variant **)p_args, p_argcount, *((Callable::CallError *)r_error));
}

/// Properties.
mesh_variant_type GDAPI mesh_variant_get_member_type(mesh_variant_type p_type, const mesh_string_name *p_member) {
	return (mesh_variant_type)Variant::get_member_type((Variant::Type)p_type, *((const StringName *)p_member));
}

mesh_variant_type GDAPI mesh_variant_get_member_type_with_cstring(mesh_variant_type p_type, const char *p_member) {
	return (mesh_variant_type)Variant::get_member_type((Variant::Type)p_type, StringName(p_member));
}

int GDAPI mesh_variant_get_member_count(mesh_variant_type p_type) {
	return Variant::get_member_count((Variant::Type)p_type);
}

void GDAPI mesh_variant_get_member_list(mesh_variant_type p_type, mesh_string_name *r_list) {
	List<StringName> members;
	Variant::get_member_list((Variant::Type)p_type, &members);
	int i = 0;
	for (const StringName &E : members) {
		memnew_placement(&r_list[i++], StringName(E));
	}
}

mesh_validated_setter GDAPI mesh_variant_get_validated_setter(mesh_variant_type p_type, const mesh_string_name *p_member) {
	return (mesh_validated_setter)Variant::get_member_validated_setter((Variant::Type)p_type, *((const StringName *)p_member));
}

mesh_validated_setter GDAPI mesh_variant_get_validated_setter_with_cstring(mesh_variant_type p_type, const char *p_member) {
	return (mesh_validated_setter)Variant::get_member_validated_setter((Variant::Type)p_type, StringName(p_member));
}

mesh_validated_getter GDAPI mesh_variant_get_validated_getter(mesh_variant_type p_type, const mesh_string_name *p_member) {
	return (mesh_validated_getter)Variant::get_member_validated_getter((Variant::Type)p_type, *((const StringName *)p_member));
}

mesh_validated_getter GDAPI mesh_variant_get_validated_getter_with_cstring(mesh_variant_type p_type, const char *p_member) {
	return (mesh_validated_getter)Variant::get_member_validated_getter((Variant::Type)p_type, StringName(p_member));
}

mesh_ptr_setter GDAPI mesh_variant_get_ptr_setter(mesh_variant_type p_type, const mesh_string_name *p_member) {
	return (mesh_ptr_setter)Variant::get_member_ptr_setter((Variant::Type)p_type, *((const StringName *)p_member));
}

mesh_ptr_setter GDAPI mesh_variant_get_ptr_setter_with_cstring(mesh_variant_type p_type, const char *p_member) {
	return (mesh_ptr_setter)Variant::get_member_ptr_setter((Variant::Type)p_type, StringName(p_member));
}

mesh_ptr_getter GDAPI mesh_variant_get_ptr_getter(mesh_variant_type p_type, const mesh_string_name *p_member) {
	return (mesh_ptr_getter)Variant::get_member_ptr_getter((Variant::Type)p_type, *((const StringName *)p_member));
}

mesh_ptr_getter GDAPI mesh_variant_get_ptr_getter_with_cstring(mesh_variant_type p_type, const char *p_member) {
	return (mesh_ptr_getter)Variant::get_member_ptr_getter((Variant::Type)p_type, StringName(p_member));
}

/// Indexing.
bool GDAPI mesh_variant_has_indexing(mesh_variant_type p_type) {
	return Variant::has_indexing((Variant::Type)p_type);
}

mesh_variant_type GDAPI mesh_variant_get_indexed_element_type(mesh_variant_type p_type) {
	return (mesh_variant_type)Variant::get_indexed_element_type((Variant::Type)p_type);
}

mesh_validated_indexed_setter GDAPI mesh_variant_get_validated_indexed_setter(mesh_variant_type p_type) {
	return (mesh_validated_indexed_setter)Variant::get_member_validated_indexed_setter((Variant::Type)p_type);
}

mesh_validated_indexed_getter GDAPI mesh_variant_get_validated_indexed_getter(mesh_variant_type p_type) {
	return (mesh_validated_indexed_getter)Variant::get_member_validated_indexed_getter((Variant::Type)p_type);
}

mesh_ptr_indexed_setter GDAPI mesh_variant_get_ptr_indexed_setter(mesh_variant_type p_type) {
	return (mesh_ptr_indexed_setter)Variant::get_member_ptr_indexed_setter((Variant::Type)p_type);
}

mesh_ptr_indexed_getter GDAPI mesh_variant_get_ptr_indexed_getter(mesh_variant_type p_type) {
	return (mesh_ptr_indexed_getter)Variant::get_member_ptr_indexed_getter((Variant::Type)p_type);
}

uint64_t GDAPI mesh_variant_get_indexed_size(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	return self->get_indexed_size();
}

/// Keying.
bool GDAPI mesh_variant_is_keyed(mesh_variant_type p_type) {
	return Variant::is_keyed((Variant::Type)p_type);
}

mesh_validated_keyed_setter GDAPI mesh_variant_get_validated_keyed_setter(mesh_variant_type p_type) {
	return (mesh_validated_keyed_setter)Variant::get_member_validated_keyed_setter((Variant::Type)p_type);
}

mesh_validated_keyed_getter GDAPI mesh_variant_get_validated_keyed_getter(mesh_variant_type p_type) {
	return (mesh_validated_keyed_getter)Variant::get_member_validated_keyed_getter((Variant::Type)p_type);
}

mesh_validated_keyed_checker GDAPI mesh_variant_get_validated_keyed_checker(mesh_variant_type p_type) {
	return (mesh_validated_keyed_checker)Variant::get_member_validated_keyed_checker((Variant::Type)p_type);
}

mesh_ptr_keyed_setter GDAPI mesh_variant_get_ptr_keyed_setter(mesh_variant_type p_type) {
	return (mesh_ptr_keyed_setter)Variant::get_member_ptr_keyed_setter((Variant::Type)p_type);
}

mesh_ptr_keyed_getter GDAPI mesh_variant_get_ptr_keyed_getter(mesh_variant_type p_type) {
	return (mesh_ptr_keyed_getter)Variant::get_member_ptr_keyed_getter((Variant::Type)p_type);
}

mesh_ptr_keyed_checker GDAPI mesh_variant_get_ptr_keyed_checker(mesh_variant_type p_type) {
	return (mesh_ptr_keyed_checker)Variant::get_member_ptr_keyed_checker((Variant::Type)p_type);
}

/// Constants.
int GDAPI mesh_variant_get_constants_count(mesh_variant_type p_type) {
	return Variant::get_constants_count_for_type((Variant::Type)p_type);
}

void GDAPI mesh_variant_get_constants_list(mesh_variant_type p_type, mesh_string_name *r_list) {
	List<StringName> constants;
	int i = 0;
	Variant::get_constants_for_type((Variant::Type)p_type, &constants);
	for (const StringName &E : constants) {
		memnew_placement(&r_list[i++], StringName(E));
	}
}

bool GDAPI mesh_variant_has_constant(mesh_variant_type p_type, const mesh_string_name *p_constant) {
	return Variant::has_constant((Variant::Type)p_type, *((const StringName *)p_constant));
}

bool GDAPI mesh_variant_has_constant_with_cstring(mesh_variant_type p_type, const char *p_constant) {
	return Variant::has_constant((Variant::Type)p_type, StringName(p_constant));
}

mesh_variant GDAPI mesh_variant_get_constant_value(mesh_variant_type p_type, const mesh_string_name *p_constant) {
	Variant constant = Variant::get_constant_value((Variant::Type)p_type, *((const StringName *)p_constant));
	mesh_variant ret;
	memnew_placement(&ret, Variant(constant));
	return ret;
}

mesh_variant GDAPI mesh_variant_get_constant_value_with_cstring(mesh_variant_type p_type, const char *p_constant) {
	Variant constant = Variant::get_constant_value((Variant::Type)p_type, StringName(p_constant));
	mesh_variant ret;
	memnew_placement(&ret, Variant(constant));
	return ret;
}

/// Utilities.
bool GDAPI mesh_variant_has_utility_function(const mesh_string_name *p_function) {
	return Variant::has_utility_function(*((const StringName *)p_function));
}

bool GDAPI mesh_variant_has_utility_function_with_cstring(const char *p_function) {
	return Variant::has_utility_function(StringName(p_function));
}

void GDAPI mesh_variant_call_utility_function(const mesh_string_name *p_function, mesh_variant *r_ret, const mesh_variant **p_args, int p_argument_count, mesh_variant_call_error *r_error) {
	const StringName *function = (const StringName *)p_function;
	Variant *ret = (Variant *)r_ret;
	const Variant **args = (const Variant **)p_args;
	Callable::CallError error;

	Variant::call_utility_function(*function, ret, args, p_argument_count, error);

	if (r_error) {
		r_error->error = (mesh_variant_call_error_error)error.error;
		r_error->argument = error.argument;
		r_error->expected = (mesh_variant_type)error.expected;
	}
}

void GDAPI mesh_variant_call_utility_function_with_cstring(const char *p_function, mesh_variant *r_ret, const mesh_variant **p_args, int p_argument_count, mesh_variant_call_error *r_error) {
	Variant *ret = (Variant *)r_ret;
	const Variant **args = (const Variant **)p_args;
	Callable::CallError error;

	Variant::call_utility_function(StringName(p_function), ret, args, p_argument_count, error);

	if (r_error) {
		r_error->error = (mesh_variant_call_error_error)error.error;
		r_error->argument = error.argument;
		r_error->expected = (mesh_variant_type)error.expected;
	}
}

mesh_ptr_utility_function GDAPI mesh_variant_get_ptr_utility_function(const mesh_string_name *p_function) {
	return (mesh_ptr_utility_function)Variant::get_ptr_utility_function(*((const StringName *)p_function));
}

mesh_ptr_utility_function GDAPI mesh_variant_get_ptr_utility_function_with_cstring(const char *p_function) {
	return (mesh_ptr_utility_function)Variant::get_ptr_utility_function(StringName(p_function));
}

mesh_validated_utility_function GDAPI mesh_variant_get_validated_utility_function(const mesh_string_name *p_function) {
	return (mesh_validated_utility_function)Variant::get_validated_utility_function(*((const StringName *)p_function));
}

mesh_validated_utility_function GDAPI mesh_variant_get_validated_utility_function_with_cstring(const char *p_function) {
	return (mesh_validated_utility_function)Variant::get_validated_utility_function(StringName(p_function));
}

mesh_variant_utility_function_type GDAPI mesh_variant_get_utility_function_type(const mesh_string_name *p_function) {
	return (mesh_variant_utility_function_type)Variant::get_utility_function_type(*((const StringName *)p_function));
}

mesh_variant_utility_function_type GDAPI mesh_variant_get_utility_function_type_with_cstring(const char *p_function) {
	return (mesh_variant_utility_function_type)Variant::get_utility_function_type(StringName(p_function));
}

int GDAPI mesh_variant_get_utility_function_argument_count(const mesh_string_name *p_function) {
	return Variant::get_utility_function_argument_count(*((const StringName *)p_function));
}

int GDAPI mesh_variant_get_utility_function_argument_count_with_cstring(const char *p_function) {
	return Variant::get_utility_function_argument_count(StringName(p_function));
}

mesh_variant_type GDAPI mesh_variant_get_utility_function_argument_type(const mesh_string_name *p_function, int p_argument) {
	return (mesh_variant_type)Variant::get_utility_function_argument_type(*((const StringName *)p_function), p_argument);
}

mesh_variant_type GDAPI mesh_variant_get_utility_function_argument_type_with_cstring(const char *p_function, int p_argument) {
	return (mesh_variant_type)Variant::get_utility_function_argument_type(StringName(p_function), p_argument);
}

mesh_string GDAPI mesh_variant_get_utility_function_argument_name(const mesh_string_name *p_function, int p_argument) {
	String argument_name = Variant::get_utility_function_argument_name(*((const StringName *)p_function), p_argument);
	mesh_string ret;
	memnew_placement(&ret, String(argument_name));
	return ret;
}

mesh_string GDAPI mesh_variant_get_utility_function_argument_name_with_cstring(const char *p_function, int p_argument) {
	String argument_name = Variant::get_utility_function_argument_name(StringName(p_function), p_argument);
	mesh_string ret;
	memnew_placement(&ret, String(argument_name));
	return ret;
}

bool GDAPI mesh_variant_has_utility_function_return_value(const mesh_string_name *p_function) {
	return Variant::has_utility_function_return_value(*((const StringName *)p_function));
}

bool GDAPI mesh_variant_has_utility_function_return_value_with_cstring(const char *p_function) {
	return Variant::has_utility_function_return_value(StringName(p_function));
}

mesh_variant_type GDAPI mesh_variant_get_utility_function_return_type(const mesh_string_name *p_function) {
	return (mesh_variant_type)Variant::get_utility_function_return_type(*((const StringName *)p_function));
}

mesh_variant_type GDAPI mesh_variant_get_utility_function_return_type_with_cstring(const char *p_function) {
	return (mesh_variant_type)Variant::get_utility_function_return_type(StringName(p_function));
}

bool GDAPI mesh_variant_is_utility_function_vararg(const mesh_string_name *p_function) {
	return Variant::is_utility_function_vararg(*((const StringName *)p_function));
}

bool GDAPI mesh_variant_is_utility_function_vararg_with_cstring(const char *p_function) {
	return Variant::is_utility_function_vararg(StringName(p_function));
}

int GDAPI mesh_variant_get_utility_function_count() {
	return Variant::get_utility_function_count();
}

void GDAPI mesh_variant_get_utility_function_list(mesh_string_name *r_functions) {
	List<StringName> functions;
	mesh_string_name *func = r_functions;
	Variant::get_utility_function_list(&functions);

	for (const StringName &E : functions) {
		memnew_placement(func++, StringName(E));
	}
}

// Introspection.

mesh_variant_type GDAPI mesh_variant_get_type(const mesh_variant *p_self) {
	const Variant *self = (const Variant *)p_self;
	return (mesh_variant_type)self->get_type();
}

bool GDAPI mesh_variant_has_method(const mesh_variant *p_self, const mesh_string_name *p_method) {
	const Variant *self = (const Variant *)p_self;
	const StringName *method = (const StringName *)p_method;
	return self->has_method(*method);
}

bool GDAPI mesh_variant_has_member(mesh_variant_type p_type, const mesh_string_name *p_member) {
	return Variant::has_member((Variant::Type)p_type, *((const StringName *)p_member));
}

bool GDAPI mesh_variant_has_key(const mesh_variant *p_self, const mesh_variant *p_key, bool *r_valid) {
	const Variant *self = (const Variant *)p_self;
	const Variant *key = (const Variant *)p_key;
	return self->has_key(*key, *r_valid);
}

mesh_string GDAPI mesh_variant_get_type_name(mesh_variant_type p_type) {
	String name = Variant::get_type_name((Variant::Type)p_type);
	mesh_string ret;
	memnew_placement(&ret, String(name));
	return ret;
}

bool GDAPI mesh_variant_can_convert(mesh_variant_type p_from, mesh_variant_type p_to) {
	return Variant::can_convert((Variant::Type)p_from, (Variant::Type)p_to);
}

bool GDAPI mesh_variant_can_convert_strict(mesh_variant_type p_from, mesh_variant_type p_to) {
	return Variant::can_convert_strict((Variant::Type)p_from, (Variant::Type)p_to);
}

#ifdef __cplusplus
}
#endif
