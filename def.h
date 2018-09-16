#ifndef RDEF_H
#define RDEF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

#ifdef __cplusplus
#define restrict
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef unsigned char byte;

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

#endif
