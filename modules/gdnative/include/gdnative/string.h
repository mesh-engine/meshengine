/*************************************************************************/
/*  string.h                                                             */
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

#ifndef MESH_STRING_H
#define MESH_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#ifndef __cplusplus
typedef uint16_t char16_t;
typedef uint32_t char32_t;
#endif

typedef char32_t mesh_char_type;

#define MESH_STRING_SIZE sizeof(void *)

#ifndef MESH_CORE_API_MESH_STRING_TYPE_DEFINED
#define MESH_CORE_API_MESH_STRING_TYPE_DEFINED
typedef struct {
	uint8_t _dont_touch_that[MESH_STRING_SIZE];
} mesh_string;
#endif

#include <gdnative/gdnative.h>
#include <gdnative/math_defs.h>

void GDAPI mesh_string_new(mesh_string *r_dest);
void GDAPI mesh_string_new_copy(mesh_string *r_dest, const mesh_string *p_src);
void GDAPI mesh_string_destroy(mesh_string *p_self);

void GDAPI mesh_string_new_with_latin1_chars(mesh_string *r_dest, const char *p_contents);
void GDAPI mesh_string_new_with_utf8_chars(mesh_string *r_dest, const char *p_contents);
void GDAPI mesh_string_new_with_utf16_chars(mesh_string *r_dest, const char16_t *p_contents);
void GDAPI mesh_string_new_with_utf32_chars(mesh_string *r_dest, const char32_t *p_contents);
void GDAPI mesh_string_new_with_wide_chars(mesh_string *r_dest, const wchar_t *p_contents);

void GDAPI mesh_string_new_with_latin1_chars_and_len(mesh_string *r_dest, const char *p_contents, const int p_size);
void GDAPI mesh_string_new_with_utf8_chars_and_len(mesh_string *r_dest, const char *p_contents, const int p_size);
void GDAPI mesh_string_new_with_utf16_chars_and_len(mesh_string *r_dest, const char16_t *p_contents, const int p_size);
void GDAPI mesh_string_new_with_utf32_chars_and_len(mesh_string *r_dest, const char32_t *p_contents, const int p_size);
void GDAPI mesh_string_new_with_wide_chars_and_len(mesh_string *r_dest, const wchar_t *p_contents, const int p_size);

const char GDAPI *mesh_string_to_latin1_chars(const mesh_string *p_self);
const char GDAPI *mesh_string_to_utf8_chars(const mesh_string *p_self);
const char16_t GDAPI *mesh_string_to_utf16_chars(const mesh_string *p_self);
const char32_t GDAPI *mesh_string_to_utf32_chars(const mesh_string *p_self);
const wchar_t GDAPI *mesh_string_to_wide_chars(const mesh_string *p_self);

char32_t GDAPI *mesh_string_operator_index(mesh_string *p_self, mesh_int p_index);
const char32_t GDAPI *mesh_string_operator_index_const(const mesh_string *p_self, mesh_int p_index);

#ifdef __cplusplus
}
#endif

#endif // MESH_STRING_H
