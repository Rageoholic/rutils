#ifndef RDEBUG_H
#define RDEBUG_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* Functions */
#ifdef NDEBUG
#define ERROR(str)
#else
#define ERROR(str)                                                              \
    do                                                                          \
    {                                                                           \
        fprintf(stderr, "fatal error at %s:%d: %s\n", __FILE__, __LINE__, str); \
        abort();                                                                \
    } while (0);
#endif

#define INVARIANT(expr, str)                                                               \
    do                                                                                     \
    {                                                                                      \
        if (!(expr))                                                                       \
        {                                                                                  \
            fprintf(stderr, "Invariant violated at %s:%d: %s\n", __FILE__, __LINE__, str); \
            abort();                                                                       \
        }                                                                                  \
    } while (0)
#endif
