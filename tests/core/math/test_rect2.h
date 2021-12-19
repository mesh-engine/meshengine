/*************************************************************************/
/*  test_rect2.h                                                         */
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

#ifndef TEST_RECT2_H
#define TEST_RECT2_H

#include "core/math/rect2.h"

#include "thirdparty/doctest/doctest.h"

namespace TestRect2 {
// We also test Rect2i here, for consistency with the source code where Rect2
// and Rect2i are defined in the same file.

// Rect2

TEST_CASE("[Rect2] Constructor methods") {
	const Rect2 rect = Rect2(0, 100, 1280, 720);
	const Rect2 rect_vector = Rect2(Vector2(0, 100), Vector2(1280, 720));
	const Rect2 rect_copy_rect = Rect2(rect);
	const Rect2 rect_copy_recti = Rect2(Rect2i(0, 100, 1280, 720));

	CHECK_MESSAGE(
			rect == rect_vector,
			"Rect2s created with the same dimensions but by different methods should be equal.");
	CHECK_MESSAGE(
			rect == rect_copy_rect,
			"Rect2s created with the same dimensions but by different methods should be equal.");
	CHECK_MESSAGE(
			rect == rect_copy_recti,
			"Rect2s created with the same dimensions but by different methods should be equal.");
}

TEST_CASE("[Rect2] String conversion") {
	// Note: This also depends on the Vector2 string representation.
	CHECK_MESSAGE(
			String(Rect2(0, 100, 1280, 720)) == "[P: (0, 100), S: (1280, 720)]",
			"The string representation should match the expected value.");
}

TEST_CASE("[Rect2] Basic getters") {
	const Rect2 rect = Rect2(0, 100, 1280, 720);
	CHECK_MESSAGE(
			rect.get_position().is_equal_approx(Vector2(0, 100)),
			"get_position() should return the expected value.");
	CHECK_MESSAGE(
			rect.get_size().is_equal_approx(Vector2(1280, 720)),
			"get_size() should return the expected value.");
	CHECK_MESSAGE(
			rect.get_end().is_equal_approx(Vector2(1280, 820)),
			"get_end() should return the expected value.");
	CHECK_MESSAGE(
			rect.get_center().is_equal_approx(Vector2(640, 460)),
			"get_center() should return the expected value.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1281, 721).get_center().is_equal_approx(Vector2(640.5, 460.5)),
			"get_center() should return the expected value.");
}

TEST_CASE("[Rect2] Basic setters") {
	Rect2 rect = Rect2(0, 100, 1280, 720);
	rect.set_end(Vector2(4000, 4000));
	CHECK_MESSAGE(
			rect.is_equal_approx(Rect2(0, 100, 4000, 3900)),
			"set_end() should result in the expected Rect2.");

	rect = Rect2(0, 100, 1280, 720);
	rect.set_position(Vector2(4000, 4000));
	CHECK_MESSAGE(
			rect.is_equal_approx(Rect2(4000, 4000, 1280, 720)),
			"set_position() should result in the expected Rect2.");

	rect = Rect2(0, 100, 1280, 720);
	rect.set_size(Vector2(4000, 4000));
	CHECK_MESSAGE(
			rect.is_equal_approx(Rect2(0, 100, 4000, 4000)),
			"set_size() should result in the expected Rect2.");
}

TEST_CASE("[Rect2] Area getters") {
	CHECK_MESSAGE(
			Math::is_equal_approx(Rect2(0, 100, 1280, 720).get_area(), 921'600),
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Math::is_equal_approx(Rect2(0, 100, -1280, -720).get_area(), 921'600),
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Math::is_equal_approx(Rect2(0, 100, 1280, -720).get_area(), -921'600),
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Math::is_equal_approx(Rect2(0, 100, -1280, 720).get_area(), -921'600),
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Math::is_zero_approx(Rect2(0, 100, 0, 720).get_area()),
			"get_area() should return the expected value.");

	CHECK_MESSAGE(
			!Rect2(0, 100, 1280, 720).has_no_area(),
			"has_no_area() should return the expected value on Rect2 with an area.");
	CHECK_MESSAGE(
			Rect2(0, 100, 0, 500).has_no_area(),
			"has_no_area() should return the expected value on Rect2 with no area.");
	CHECK_MESSAGE(
			Rect2(0, 100, 500, 0).has_no_area(),
			"has_no_area() should return the expected value on Rect2 with no area.");
	CHECK_MESSAGE(
			Rect2(0, 100, 0, 0).has_no_area(),
			"has_no_area() should return the expected value on Rect2 with no area.");
}

TEST_CASE("[Rect2] Absolute coordinates") {
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).abs().is_equal_approx(Rect2(0, 100, 1280, 720)),
			"abs() should return the expected Rect2.");
	CHECK_MESSAGE(
			Rect2(0, -100, 1280, 720).abs().is_equal_approx(Rect2(0, -100, 1280, 720)),
			"abs() should return the expected Rect2.");
	CHECK_MESSAGE(
			Rect2(0, -100, -1280, -720).abs().is_equal_approx(Rect2(-1280, -820, 1280, 720)),
			"abs() should return the expected Rect2.");
	CHECK_MESSAGE(
			Rect2(0, 100, -1280, 720).abs().is_equal_approx(Rect2(-1280, 100, 1280, 720)),
			"abs() should return the expected Rect2.");
}

TEST_CASE("[Rect2] Intersection") {
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).intersection(Rect2(0, 300, 100, 100)).is_equal_approx(Rect2(0, 300, 100, 100)),
			"intersection() with fully enclosed Rect2 should return the expected result.");
	// The resulting Rect2 is 100 pixels high because the first Rect2 is vertically offset by 100 pixels.
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).intersection(Rect2(1200, 700, 100, 100)).is_equal_approx(Rect2(1200, 700, 80, 100)),
			"intersection() with partially enclosed Rect2 should return the expected result.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).intersection(Rect2(-4000, -4000, 100, 100)).is_equal_approx(Rect2()),
			"intersection() with non-enclosed Rect2 should return the expected result.");
}

TEST_CASE("[Rect2] Enclosing") {
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).encloses(Rect2(0, 300, 100, 100)),
			"encloses() with fully contained Rect2 should return the expected result.");
	CHECK_MESSAGE(
			!Rect2(0, 100, 1280, 720).encloses(Rect2(1200, 700, 100, 100)),
			"encloses() with partially contained Rect2 should return the expected result.");
	CHECK_MESSAGE(
			!Rect2(0, 100, 1280, 720).encloses(Rect2(-4000, -4000, 100, 100)),
			"encloses() with non-contained Rect2 should return the expected result.");
}

TEST_CASE("[Rect2] Expanding") {
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).expand(Vector2(500, 600)).is_equal_approx(Rect2(0, 100, 1280, 720)),
			"expand() with contained Vector2 should return the expected result.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).expand(Vector2(0, 0)).is_equal_approx(Rect2(0, 0, 1280, 820)),
			"expand() with non-contained Vector2 should return the expected result.");
}

TEST_CASE("[Rect2] Growing") {
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).grow(100).is_equal_approx(Rect2(-100, 0, 1480, 920)),
			"grow() with positive value should return the expected Rect2.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).grow(-100).is_equal_approx(Rect2(100, 200, 1080, 520)),
			"grow() with negative value should return the expected Rect2.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).grow(-4000).is_equal_approx(Rect2(4000, 4100, -6720, -7280)),
			"grow() with large negative value should return the expected Rect2.");

	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).grow_individual(100, 200, 300, 400).is_equal_approx(Rect2(-100, -100, 1680, 1320)),
			"grow_individual() with positive values should return the expected Rect2.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).grow_individual(-100, 200, 300, -400).is_equal_approx(Rect2(100, -100, 1480, 520)),
			"grow_individual() with positive and negative values should return the expected Rect2.");

	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).grow_side(SIDE_TOP, 500).is_equal_approx(Rect2(0, -400, 1280, 1220)),
			"grow_side() with positive value should return the expected Rect2.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).grow_side(SIDE_TOP, -500).is_equal_approx(Rect2(0, 600, 1280, 220)),
			"grow_side() with negative value should return the expected Rect2.");
}

TEST_CASE("[Rect2] Has point") {
	Rect2 rect = Rect2(0, 100, 1280, 720);
	CHECK_MESSAGE(
			rect.has_point(Vector2(500, 600)),
			"has_point() with contained Vector2 should return the expected result.");
	CHECK_MESSAGE(
			!rect.has_point(Vector2(0, 0)),
			"has_point() with non-contained Vector2 should return the expected result.");

	CHECK_MESSAGE(
			rect.has_point(rect.position),
			"has_point() with positive size should include `position`.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2(1, 1)),
			"has_point() with positive size should include `position + (1, 1)`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2(1, -1)),
			"has_point() with positive size should not include `position + (1, -1)`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size),
			"has_point() with positive size should not include `position + size`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size + Vector2(1, 1)),
			"has_point() with positive size should not include `position + size + (1, 1)`.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + rect.size + Vector2(-1, -1)),
			"has_point() with positive size should include `position + size + (-1, -1)`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size + Vector2(-1, 1)),
			"has_point() with positive size should not include `position + size + (-1, 1)`.");

	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2(0, 10)),
			"has_point() with point located on left edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2(rect.size.x, 10)),
			"has_point() with point located on right edge should return false.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2(10, 0)),
			"has_point() with point located on top edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2(10, rect.size.y)),
			"has_point() with point located on bottom edge should return false.");

	/*
	// FIXME: Disabled for now until GH-37617 is fixed one way or another.
	// More tests should then be written like for the positive size case.
	rect = Rect2(0, 100, -1280, -720);
	CHECK_MESSAGE(
			rect.has_point(rect.position),
			"has_point() with negative size should include `position`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size),
			"has_point() with negative size should not include `position + size`.");
	*/

	rect = Rect2(-4000, -200, 1280, 720);
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2(0, 10)),
			"has_point() with negative position and point located on left edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2(rect.size.x, 10)),
			"has_point() with negative position and point located on right edge should return false.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2(10, 0)),
			"has_point() with negative position and point located on top edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2(10, rect.size.y)),
			"has_point() with negative position and point located on bottom edge should return false.");
}

TEST_CASE("[Rect2] Intersection") {
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).intersects(Rect2(0, 300, 100, 100)),
			"intersects() with fully enclosed Rect2 should return the expected result.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).intersects(Rect2(1200, 700, 100, 100)),
			"intersects() with partially enclosed Rect2 should return the expected result.");
	CHECK_MESSAGE(
			!Rect2(0, 100, 1280, 720).intersects(Rect2(-4000, -4000, 100, 100)),
			"intersects() with non-enclosed Rect2 should return the expected result.");
}

TEST_CASE("[Rect2] Merging") {
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).merge(Rect2(0, 300, 100, 100)).is_equal_approx(Rect2(0, 100, 1280, 720)),
			"merge() with fully enclosed Rect2 should return the expected result.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).merge(Rect2(1200, 700, 100, 100)).is_equal_approx(Rect2(0, 100, 1300, 720)),
			"merge() with partially enclosed Rect2 should return the expected result.");
	CHECK_MESSAGE(
			Rect2(0, 100, 1280, 720).merge(Rect2(-4000, -4000, 100, 100)).is_equal_approx(Rect2(-4000, -4000, 5280, 4820)),
			"merge() with non-enclosed Rect2 should return the expected result.");
}

// Rect2i

TEST_CASE("[Rect2i] Constructor methods") {
	Rect2i recti = Rect2i(0, 100, 1280, 720);
	Rect2i recti_vector = Rect2i(Vector2i(0, 100), Vector2i(1280, 720));
	Rect2i recti_copy_recti = Rect2i(recti);
	Rect2i recti_copy_rect = Rect2i(Rect2(0, 100, 1280, 720));

	CHECK_MESSAGE(
			recti == recti_vector,
			"Rect2is created with the same dimensions but by different methods should be equal.");
	CHECK_MESSAGE(
			recti == recti_copy_recti,
			"Rect2is created with the same dimensions but by different methods should be equal.");
	CHECK_MESSAGE(
			recti == recti_copy_rect,
			"Rect2is created with the same dimensions but by different methods should be equal.");
}

TEST_CASE("[Rect2i] String conversion") {
	// Note: This also depends on the Vector2 string representation.
	CHECK_MESSAGE(
			String(Rect2i(0, 100, 1280, 720)) == "[P: (0, 100), S: (1280, 720)]",
			"The string representation should match the expected value.");
}

TEST_CASE("[Rect2i] Basic getters") {
	const Rect2i rect = Rect2i(0, 100, 1280, 720);
	CHECK_MESSAGE(
			rect.get_position() == Vector2i(0, 100),
			"get_position() should return the expected value.");
	CHECK_MESSAGE(
			rect.get_size() == Vector2i(1280, 720),
			"get_size() should return the expected value.");
	CHECK_MESSAGE(
			rect.get_end() == Vector2i(1280, 820),
			"get_end() should return the expected value.");
	CHECK_MESSAGE(
			rect.get_center() == Vector2i(640, 460),
			"get_center() should return the expected value.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1281, 721).get_center() == Vector2i(640, 460),
			"get_center() should return the expected value.");
}

TEST_CASE("[Rect2i] Basic setters") {
	Rect2i rect = Rect2i(0, 100, 1280, 720);
	rect.set_end(Vector2i(4000, 4000));
	CHECK_MESSAGE(
			rect == Rect2i(0, 100, 4000, 3900),
			"set_end() should result in the expected Rect2i.");

	rect = Rect2i(0, 100, 1280, 720);
	rect.set_position(Vector2i(4000, 4000));
	CHECK_MESSAGE(
			rect == Rect2i(4000, 4000, 1280, 720),
			"set_position() should result in the expected Rect2i.");

	rect = Rect2i(0, 100, 1280, 720);
	rect.set_size(Vector2i(4000, 4000));
	CHECK_MESSAGE(
			rect == Rect2i(0, 100, 4000, 4000),
			"set_size() should result in the expected Rect2i.");
}

TEST_CASE("[Rect2i] Area getters") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).get_area() == 921'600,
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Rect2i(0, 100, -1280, -720).get_area() == 921'600,
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, -720).get_area() == -921'600,
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Rect2i(0, 100, -1280, 720).get_area() == -921'600,
			"get_area() should return the expected value.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 0, 720).get_area() == 0,
			"get_area() should return the expected value.");

	CHECK_MESSAGE(
			!Rect2i(0, 100, 1280, 720).has_no_area(),
			"has_no_area() should return the expected value on Rect2i with an area.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 0, 500).has_no_area(),
			"has_no_area() should return the expected value on Rect2i with no area.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 500, 0).has_no_area(),
			"has_no_area() should return the expected value on Rect2i with no area.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 0, 0).has_no_area(),
			"has_no_area() should return the expected value on Rect2i with no area.");
}

TEST_CASE("[Rect2i] Absolute coordinates") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).abs() == Rect2i(0, 100, 1280, 720),
			"abs() should return the expected Rect2i.");
	CHECK_MESSAGE(
			Rect2i(0, -100, 1280, 720).abs() == Rect2i(0, -100, 1280, 720),
			"abs() should return the expected Rect2i.");
	CHECK_MESSAGE(
			Rect2i(0, -100, -1280, -720).abs() == Rect2i(-1280, -820, 1280, 720),
			"abs() should return the expected Rect2i.");
	CHECK_MESSAGE(
			Rect2i(0, 100, -1280, 720).abs() == Rect2i(-1280, 100, 1280, 720),
			"abs() should return the expected Rect2i.");
}

TEST_CASE("[Rect2i] Intersection") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).intersection(Rect2i(0, 300, 100, 100)) == Rect2i(0, 300, 100, 100),
			"intersection() with fully enclosed Rect2i should return the expected result.");
	// The resulting Rect2i is 100 pixels high because the first Rect2i is vertically offset by 100 pixels.
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).intersection(Rect2i(1200, 700, 100, 100)) == Rect2i(1200, 700, 80, 100),
			"intersection() with partially enclosed Rect2i should return the expected result.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).intersection(Rect2i(-4000, -4000, 100, 100)) == Rect2i(),
			"intersection() with non-enclosed Rect2i should return the expected result.");
}

TEST_CASE("[Rect2i] Enclosing") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).encloses(Rect2i(0, 300, 100, 100)),
			"encloses() with fully contained Rect2i should return the expected result.");
	CHECK_MESSAGE(
			!Rect2i(0, 100, 1280, 720).encloses(Rect2i(1200, 700, 100, 100)),
			"encloses() with partially contained Rect2i should return the expected result.");
	CHECK_MESSAGE(
			!Rect2i(0, 100, 1280, 720).encloses(Rect2i(-4000, -4000, 100, 100)),
			"encloses() with non-contained Rect2i should return the expected result.");
}

TEST_CASE("[Rect2i] Expanding") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).expand(Vector2i(500, 600)) == Rect2i(0, 100, 1280, 720),
			"expand() with contained Vector2i should return the expected result.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).expand(Vector2i(0, 0)) == Rect2i(0, 0, 1280, 820),
			"expand() with non-contained Vector2i should return the expected result.");
}

TEST_CASE("[Rect2i] Growing") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).grow(100) == Rect2i(-100, 0, 1480, 920),
			"grow() with positive value should return the expected Rect2i.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).grow(-100) == Rect2i(100, 200, 1080, 520),
			"grow() with negative value should return the expected Rect2i.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).grow(-4000) == Rect2i(4000, 4100, -6720, -7280),
			"grow() with large negative value should return the expected Rect2i.");

	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).grow_individual(100, 200, 300, 400) == Rect2i(-100, -100, 1680, 1320),
			"grow_individual() with positive values should return the expected Rect2i.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).grow_individual(-100, 200, 300, -400) == Rect2i(100, -100, 1480, 520),
			"grow_individual() with positive and negative values should return the expected Rect2i.");

	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).grow_side(SIDE_TOP, 500) == Rect2i(0, -400, 1280, 1220),
			"grow_side() with positive value should return the expected Rect2i.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).grow_side(SIDE_TOP, -500) == Rect2i(0, 600, 1280, 220),
			"grow_side() with negative value should return the expected Rect2i.");
}

TEST_CASE("[Rect2i] Has point") {
	Rect2i rect = Rect2i(0, 100, 1280, 720);
	CHECK_MESSAGE(
			rect.has_point(Vector2i(500, 600)),
			"has_point() with contained Vector2i should return the expected result.");
	CHECK_MESSAGE(
			!rect.has_point(Vector2i(0, 0)),
			"has_point() with non-contained Vector2i should return the expected result.");

	CHECK_MESSAGE(
			rect.has_point(rect.position),
			"has_point() with positive size should include `position`.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2i(1, 1)),
			"has_point() with positive size should include `position + (1, 1)`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2i(1, -1)),
			"has_point() with positive size should not include `position + (1, -1)`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size),
			"has_point() with positive size should not include `position + size`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size + Vector2i(1, 1)),
			"has_point() with positive size should not include `position + size + (1, 1)`.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + rect.size + Vector2i(-1, -1)),
			"has_point() with positive size should include `position + size + (-1, -1)`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size + Vector2i(-1, 1)),
			"has_point() with positive size should not include `position + size + (-1, 1)`.");

	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2i(0, 10)),
			"has_point() with point located on left edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2i(rect.size.x, 10)),
			"has_point() with point located on right edge should return false.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2i(10, 0)),
			"has_point() with point located on top edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2i(10, rect.size.y)),
			"has_point() with point located on bottom edge should return false.");

	/*
	// FIXME: Disabled for now until GH-37617 is fixed one way or another.
	// More tests should then be written like for the positive size case.
	rect = Rect2i(0, 100, -1280, -720);
	CHECK_MESSAGE(
			rect.has_point(rect.position),
			"has_point() with negative size should include `position`.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + rect.size),
			"has_point() with negative size should not include `position + size`.");
	*/

	rect = Rect2i(-4000, -200, 1280, 720);
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2i(0, 10)),
			"has_point() with negative position and point located on left edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2i(rect.size.x, 10)),
			"has_point() with negative position and point located on right edge should return false.");
	CHECK_MESSAGE(
			rect.has_point(rect.position + Vector2i(10, 0)),
			"has_point() with negative position and point located on top edge should return true.");
	CHECK_MESSAGE(
			!rect.has_point(rect.position + Vector2i(10, rect.size.y)),
			"has_point() with negative position and point located on bottom edge should return false.");
}

TEST_CASE("[Rect2i] Intersection") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).intersects(Rect2i(0, 300, 100, 100)),
			"intersects() with fully enclosed Rect2i should return the expected result.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).intersects(Rect2i(1200, 700, 100, 100)),
			"intersects() with partially enclosed Rect2i should return the expected result.");
	CHECK_MESSAGE(
			!Rect2i(0, 100, 1280, 720).intersects(Rect2i(-4000, -4000, 100, 100)),
			"intersects() with non-enclosed Rect2i should return the expected result.");
}

TEST_CASE("[Rect2i] Merging") {
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).merge(Rect2i(0, 300, 100, 100)) == Rect2i(0, 100, 1280, 720),
			"merge() with fully enclosed Rect2i should return the expected result.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).merge(Rect2i(1200, 700, 100, 100)) == Rect2i(0, 100, 1300, 720),
			"merge() with partially enclosed Rect2i should return the expected result.");
	CHECK_MESSAGE(
			Rect2i(0, 100, 1280, 720).merge(Rect2i(-4000, -4000, 100, 100)) == Rect2i(-4000, -4000, 5280, 4820),
			"merge() with non-enclosed Rect2i should return the expected result.");
}
} // namespace TestRect2

#endif // TEST_RECT2_H
