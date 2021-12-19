#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

// -- MESH start --
#include <zlib.h> // Should come before including tinyexr.
// -- MESH end --

#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"
