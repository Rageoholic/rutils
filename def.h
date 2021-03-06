/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef RDEF_H
#define RDEF_H

#include <inttypes.h>

#include <stddef.h>

#ifndef NDEBUG
#define DEBUG 1
#endif

typedef int errcode;

#undef ERROR_SUCCESS
#define ERROR_SUCCESS 0
#undef ERROR_INITIALIZATION_FAILURE
#define ERROR_INITIALIZATION_FAILURE 1
#undef ERROR_NULL_PARAMETER
#define ERROR_NULL_PARAMETER 2
#undef ERROR_NO_MEMORY
#define ERROR_NO_MEMORY 3
#define ERROR_EXTERNAL_LIB 4
#define ERROR_INVAL_PARAMETER 5

#ifdef __cplusplus
#define restrict
#endif

#ifndef __cplusplus

/* An actually tolerable bool type how do all these standards fuck this up my
   god this isn't hard */
#undef bool
#ifndef __cplusplus
typedef unsigned char bool;
#endif
#define bool bool

#undef true
#define true 1
#undef false
#define false 0
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef uint_least8_t uleast8;
typedef uint_least16_t uleast16;
typedef uint_least32_t uleast32;
typedef uint_least64_t uleast64;

typedef uint_fast8_t ufast8;
typedef uint_fast16_t ufast16;
typedef uint_fast32_t ufast32;
typedef uint_fast64_t ufast64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef int_least8_t ileast8;
typedef int_least16_t ileast16;
typedef int_least32_t ileast32;
typedef int_least64_t ileast64;

typedef int_fast8_t ifast8;
typedef int_fast16_t ifast16;
typedef int_fast32_t ifast32;
typedef int_fast64_t ifast64;

typedef unsigned char byte;

typedef float f32;
typedef double f64;

typedef unsigned uint;

/* Types and constants */

#define local static  /* Function is local to the file */
#define global static /* Variable is global throughout the file */

#define ignore (void)/* Ignore this variable. Turns off warnings for unused \
                        vars in functions that care */

typedef int ReadFlags; /* Set of flags for reading files. See
                          DEFINEs with ReadFlags */

#define READ_PEEK 0x01 /* ReadFlags: Don't actually advance \
                          the buffer */

#define READ_NO_BLOCK 0x02 /* ReadFlags: Don't block on reading \
                              data from the descriptor */

#ifdef __GNUC__
#define DEPRECATED(func) func __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif

typedef int64_t ssize_t;

#define NO_GIVEN_LEN -1

typedef intptr_t isize;
typedef size_t usize;

#define countof(x) (sizeof(x) / sizeof(x[0]))

#define KILOBYTES(x) (1024 * (x))
#define MEGABYTES(x) (1024 * (KILOBYTES(x)))
#define GIGABYTES(x) (1024L * (MEGABYTES(x)))


#endif
