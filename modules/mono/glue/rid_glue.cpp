/*************************************************************************/
/*  rid_glue.cpp                                                         */
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

#ifdef MONO_GLUE_ENABLED

#include "core/io/resource.h"
#include "core/object/class_db.h"
#include "core/templates/rid.h"

#include "../mono_gd/gd_mono_marshal.h"

RID *mesh_icall_RID_Ctor(Object *p_from) {
	Resource *res_from = Object::cast_to<Resource>(p_from);

	if (res_from) {
		return memnew(RID(res_from->get_rid()));
	}

	return memnew(RID);
}

void mesh_icall_RID_Dtor(RID *p_ptr) {
	ERR_FAIL_NULL(p_ptr);
	memdelete(p_ptr);
}

uint32_t mesh_icall_RID_get_id(RID *p_ptr) {
	return p_ptr->get_id();
}

void mesh_register_rid_icalls() {
	GDMonoUtils::add_internal_call("Mesh.RID::mesh_icall_RID_Ctor", mesh_icall_RID_Ctor);
	GDMonoUtils::add_internal_call("Mesh.RID::mesh_icall_RID_Dtor", mesh_icall_RID_Dtor);
	GDMonoUtils::add_internal_call("Mesh.RID::mesh_icall_RID_get_id", mesh_icall_RID_get_id);
}

#endif // MONO_GLUE_ENABLED
