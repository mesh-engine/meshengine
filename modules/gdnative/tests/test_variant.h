/*************************************************************************/
/*  test_variant.h                                                       */
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

#ifndef TEST_GDNATIVE_VARIANT_H
#define TEST_GDNATIVE_VARIANT_H

#include <gdnative/gdnative.h>
#include <gdnative/variant.h>

#include "tests/test_macros.h"

namespace TestGDNativeVariant {

TEST_CASE("[GDNative Variant] New Variant with copy") {
	mesh_variant src;
	mesh_variant_new_int(&src, 42);

	mesh_variant copy;
	mesh_variant_new_copy(&copy, &src);

	CHECK(mesh_variant_as_int(&copy) == 42);
	CHECK(mesh_variant_get_type(&copy) == MESH_VARIANT_TYPE_INT);

	mesh_variant_destroy(&src);
	mesh_variant_destroy(&copy);
}

TEST_CASE("[GDNative Variant] New Variant with Nil") {
	mesh_variant val;
	mesh_variant_new_nil(&val);

	CHECK(mesh_variant_get_type(&val) == MESH_VARIANT_TYPE_NIL);

	mesh_variant_destroy(&val);
}

TEST_CASE("[GDNative Variant] New Variant with bool") {
	mesh_variant val;
	mesh_variant_new_bool(&val, true);

	CHECK(mesh_variant_as_bool(&val));
	CHECK(mesh_variant_get_type(&val) == MESH_VARIANT_TYPE_BOOL);

	mesh_variant_destroy(&val);
}

TEST_CASE("[GDNative Variant] New Variant with float") {
	mesh_variant val;
	mesh_variant_new_float(&val, 4.2);

	CHECK(mesh_variant_as_float(&val) == 4.2);
	CHECK(mesh_variant_get_type(&val) == MESH_VARIANT_TYPE_FLOAT);

	mesh_variant_destroy(&val);
}

TEST_CASE("[GDNative Variant] New Variant with String") {
	String str = "something";

	mesh_variant val;
	mesh_variant_new_string(&val, (mesh_string *)&str);
	mesh_string gd_str = mesh_variant_as_string(&val);
	String *result = (String *)&gd_str;

	CHECK(*result == String("something"));
	CHECK(mesh_variant_get_type(&val) == MESH_VARIANT_TYPE_STRING);

	mesh_variant_destroy(&val);
	mesh_string_destroy(&gd_str);
}

TEST_CASE("[GDNative Variant] Variant call") {
	String str("something");
	mesh_variant self;
	mesh_variant_new_string(&self, (mesh_string *)&str);

	mesh_variant ret;

	mesh_string_name method;
	mesh_string_name_new_with_latin1_chars(&method, "is_valid_identifier");

	mesh_variant_call_error error;
	mesh_variant_call(&self, &method, nullptr, 0, &ret, &error);

	CHECK(mesh_variant_get_type(&ret) == MESH_VARIANT_TYPE_BOOL);
	CHECK(mesh_variant_as_bool(&ret));

	mesh_variant_destroy(&ret);
	mesh_variant_destroy(&self);
	mesh_string_name_destroy(&method);
}

TEST_CASE("[GDNative Variant] Variant evaluate") {
	mesh_variant one;
	mesh_variant_new_int(&one, 1);
	mesh_variant two;
	mesh_variant_new_int(&two, 2);

	mesh_variant three;
	mesh_variant_new_nil(&three);
	bool valid = false;

	mesh_variant_evaluate(MESH_VARIANT_OP_ADD, &one, &two, &three, &valid);

	CHECK(mesh_variant_get_type(&three) == MESH_VARIANT_TYPE_INT);
	CHECK(mesh_variant_as_int(&three) == 3);
	CHECK(valid);

	mesh_variant_destroy(&one);
	mesh_variant_destroy(&two);
	mesh_variant_destroy(&three);
}

TEST_CASE("[GDNative Variant] Variant set/get named") {
	mesh_string_name x;
	mesh_string_name_new_with_latin1_chars(&x, "x");

	Vector2 vec(0, 0);
	mesh_variant self;
	mesh_variant_new_vector2(&self, (mesh_vector2 *)&vec);

	mesh_variant set;
	mesh_variant_new_float(&set, 1.0);

	bool set_valid = false;
	mesh_variant_set_named(&self, &x, &set, &set_valid);

	bool get_valid = false;
	mesh_variant get = mesh_variant_get_named(&self, &x, &get_valid);

	CHECK(get_valid);
	CHECK(set_valid);
	CHECK(mesh_variant_get_type(&get) == MESH_VARIANT_TYPE_FLOAT);
	CHECK(mesh_variant_as_float(&get) == 1.0);

	mesh_string_name_destroy(&x);
	mesh_variant_destroy(&self);
	mesh_variant_destroy(&set);
	mesh_variant_destroy(&get);
}

TEST_CASE("[GDNative Variant] Get utility function argument name") {
	mesh_string_name function;
	mesh_string_name_new_with_latin1_chars(&function, "pow");

	mesh_string arg_name = mesh_variant_get_utility_function_argument_name(&function, 0);

	String *arg_name_str = (String *)&arg_name;

	CHECK(*arg_name_str == "base");

	mesh_string_destroy(&arg_name);
	mesh_string_name_destroy(&function);
}

TEST_CASE("[GDNative Variant] Get utility function list") {
	int count = mesh_variant_get_utility_function_count();

	mesh_string_name *c_list = (mesh_string_name *)mesh_alloc(count * sizeof(mesh_string_name));
	mesh_variant_get_utility_function_list(c_list);

	List<StringName> cpp_list;
	Variant::get_utility_function_list(&cpp_list);

	mesh_string_name *cur = c_list;

	for (const StringName &E : cpp_list) {
		const StringName &cpp_name = E;
		StringName *c_name = (StringName *)cur++;

		CHECK(*c_name == cpp_name);
	}

	mesh_free(c_list);
}
} // namespace TestGDNativeVariant

#endif // TEST_GDNATIVE_VARIANT_H
