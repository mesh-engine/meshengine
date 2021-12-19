/*************************************************************************/
/*  gdnative.h                                                           */
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

#ifndef MESH_GDNATIVE_H
#define MESH_GDNATIVE_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(__ANDROID__)
#define GDCALLINGCONV
#define GDAPI GDCALLINGCONV
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#define GDCALLINGCONV __attribute__((visibility("default")))
#define GDAPI GDCALLINGCONV
#elif TARGET_OS_MAC
#define GDCALLINGCONV __attribute__((sysv_abi))
#define GDAPI GDCALLINGCONV
#endif
#else // !_WIN32 && !__APPLE__
#define GDCALLINGCONV __attribute__((sysv_abi))
#define GDAPI GDCALLINGCONV
#endif

// This is for libraries *using* the header, NOT MESH EXPOSING STUFF!!
#ifdef __GNUC__
#define GDN_EXPORT __attribute__((visibility("default")))
#elif defined(_WIN32)
#define GDN_EXPORT __declspec(dllexport)
#else
#define GDN_EXPORT
#endif

#include <stdbool.h>
#include <stdint.h>

////// Error

typedef enum {
	MESH_OK, // (0)
	MESH_FAILED, ///< Generic fail error
	MESH_ERR_UNAVAILABLE, ///< What is requested is unsupported/unavailable
	MESH_ERR_UNCONFIGURED, ///< The object being used hasn't been properly set up yet
	MESH_ERR_UNAUTHORIZED, ///< Missing credentials for requested resource
	MESH_ERR_PARAMETER_RANGE_ERROR, ///< Parameter given out of range (5)
	MESH_ERR_OUT_OF_MEMORY, ///< Out of memory
	MESH_ERR_FILE_NOT_FOUND,
	MESH_ERR_FILE_BAD_DRIVE,
	MESH_ERR_FILE_BAD_PATH,
	MESH_ERR_FILE_NO_PERMISSION, // (10)
	MESH_ERR_FILE_ALREADY_IN_USE,
	MESH_ERR_FILE_CANT_OPEN,
	MESH_ERR_FILE_CANT_WRITE,
	MESH_ERR_FILE_CANT_READ,
	MESH_ERR_FILE_UNRECOGNIZED, // (15)
	MESH_ERR_FILE_CORRUPT,
	MESH_ERR_FILE_MISSING_DEPENDENCIES,
	MESH_ERR_FILE_EOF,
	MESH_ERR_CANT_OPEN, ///< Can't open a resource/socket/file
	MESH_ERR_CANT_CREATE, // (20)
	MESH_ERR_QUERY_FAILED,
	MESH_ERR_ALREADY_IN_USE,
	MESH_ERR_LOCKED, ///< resource is locked
	MESH_ERR_TIMEOUT,
	MESH_ERR_CANT_CONNECT, // (25)
	MESH_ERR_CANT_RESOLVE,
	MESH_ERR_CONNECTION_ERROR,
	MESH_ERR_CANT_ACQUIRE_RESOURCE,
	MESH_ERR_CANT_FORK,
	MESH_ERR_INVALID_DATA, ///< Data passed is invalid (30)
	MESH_ERR_INVALID_PARAMETER, ///< Parameter passed is invalid
	MESH_ERR_ALREADY_EXISTS, ///< When adding, item already exists
	MESH_ERR_DOES_NOT_EXIST, ///< When retrieving/erasing, it item does not exist
	MESH_ERR_DATABASE_CANT_READ, ///< database is full
	MESH_ERR_DATABASE_CANT_WRITE, ///< database is full (35)
	MESH_ERR_COMPILATION_FAILED,
	MESH_ERR_METHOD_NOT_FOUND,
	MESH_ERR_LINK_FAILED,
	MESH_ERR_SCRIPT_FAILED,
	MESH_ERR_CYCLIC_LINK, // (40)
	MESH_ERR_INVALID_DECLARATION,
	MESH_ERR_DUPLICATE_SYMBOL,
	MESH_ERR_PARSE_ERROR,
	MESH_ERR_BUSY,
	MESH_ERR_SKIP, // (45)
	MESH_ERR_HELP, ///< user requested help!!
	MESH_ERR_BUG, ///< a bug in the software certainly happened, due to a double check failing or unexpected behavior.
	MESH_ERR_PRINTER_ON_FIRE, /// the parallel port printer is engulfed in flames
} mesh_error;

/////// Object (forward declared)
typedef void mesh_object;

/////// String

#include <gdnative/string.h>

/////// String name

#include <gdnative/string_name.h>

////// Vector2 & Vector2i

#include <gdnative/vector2.h>

////// Rect2 & Rect2i

#include <gdnative/rect2.h>

////// Vector3 & Vector3i

#include <gdnative/vector3.h>

////// Transform2D

#include <gdnative/transform2d.h>

/////// Plane

#include <gdnative/plane.h>

/////// Quaternion

#include <gdnative/quaternion.h>

/////// AABB

#include <gdnative/aabb.h>

/////// Basis

#include <gdnative/basis.h>

/////// Transform3D

#include <gdnative/transform_3d.h>

/////// Color

#include <gdnative/color.h>

/////// NodePath

#include <gdnative/node_path.h>

/////// RID

#include <gdnative/rid.h>

/////// Callable & Signal

#include <gdnative/callable.h>

/////// Dictionary

#include <gdnative/dictionary.h>

/////// Array

#include <gdnative/array.h>

// single API file for Packed*Array
#include <gdnative/packed_arrays.h>

void GDAPI mesh_object_destroy(mesh_object *p_o);

////// Variant

#include <gdnative/variant.h>

////// Singleton API

mesh_object GDAPI *mesh_global_get_singleton(char *p_name); // Result shouldn't be freed.

////// MethodBind API

typedef struct {
	uint8_t _dont_touch_that[1]; // TODO
} mesh_method_bind;

mesh_method_bind GDAPI *mesh_method_bind_get_method(const char *p_classname, const char *p_methodname);
void GDAPI mesh_method_bind_ptrcall(mesh_method_bind *p_method_bind, mesh_object *p_instance, const void **p_args, void *p_ret);
mesh_variant GDAPI mesh_method_bind_call(mesh_method_bind *p_method_bind, mesh_object *p_instance, const mesh_variant **p_args, const int p_arg_count, mesh_variant_call_error *p_call_error);
////// Script API

typedef struct mesh_gdnative_api_version {
	unsigned int major;
	unsigned int minor;
} mesh_gdnative_api_version;

typedef struct mesh_gdnative_api_struct mesh_gdnative_api_struct;

struct mesh_gdnative_api_struct {
	unsigned int type;
	mesh_gdnative_api_version version;
	const mesh_gdnative_api_struct *next;
};

#define GDNATIVE_VERSION_COMPATIBLE(want, have) (want.major == have.major && want.minor <= have.minor)

typedef struct {
	mesh_bool in_editor;
	uint64_t core_api_hash;
	uint64_t editor_api_hash;
	uint64_t no_api_hash;
	void (*report_version_mismatch)(const mesh_object *p_library, const char *p_what, mesh_gdnative_api_version p_want, mesh_gdnative_api_version p_have);
	void (*report_loading_error)(const mesh_object *p_library, const char *p_what);
	mesh_object *gd_native_library; // pointer to GDNativeLibrary that is being initialized
	const struct mesh_gdnative_core_api_struct *api_struct;
	const mesh_string *active_library_path;
} mesh_gdnative_init_options;

typedef struct {
	mesh_bool in_editor;
} mesh_gdnative_terminate_options;

// Calling convention?
typedef mesh_object *(*mesh_class_constructor)();

mesh_class_constructor GDAPI mesh_get_class_constructor(const char *p_classname);

mesh_dictionary GDAPI mesh_get_global_constants();

////// GDNative procedure types
typedef void (*mesh_gdnative_init_fn)(mesh_gdnative_init_options *);
typedef void (*mesh_gdnative_terminate_fn)(mesh_gdnative_terminate_options *);
typedef mesh_variant (*mesh_gdnative_procedure_fn)(mesh_array *);

////// System Functions

typedef mesh_variant (*native_call_cb)(void *, mesh_array *);
void GDAPI mesh_register_native_call_type(const char *p_call_type, native_call_cb p_callback);

//using these will help Mesh track how much memory is in use in debug mode
void GDAPI *mesh_alloc(int p_bytes);
void GDAPI *mesh_realloc(void *p_ptr, int p_bytes);
void GDAPI mesh_free(void *p_ptr);

// Helper print functions.
void GDAPI mesh_print_error(const char *p_description, const char *p_function, const char *p_file, int p_line);
void GDAPI mesh_print_warning(const char *p_description, const char *p_function, const char *p_file, int p_line);
void GDAPI mesh_print_script_error(const char *p_description, const char *p_function, const char *p_file, int p_line);

//tags used for safe dynamic casting
void GDAPI *mesh_get_class_tag(const mesh_string_name *p_class);
mesh_object GDAPI *mesh_object_cast_to(const mesh_object *p_object, void *p_class_tag);

// equivalent of GDScript's instance_from_id
mesh_object GDAPI *mesh_instance_from_id(uint64_t p_instance_id);

uint64_t GDAPI mesh_object_get_instance_id(const mesh_object *p_object);

#ifdef __cplusplus
}
#endif

#endif // MESH_GDNATIVE_H
