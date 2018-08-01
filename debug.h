#ifndef RDEBUG_H
#define RDEBUG_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* Functions */
#ifdef NDEBUG
#define ERROR(str)
#else
#define ERROR(str)                                                            \
    do                                                                        \
    {                                                                         \
        fprintf(stderr, "fatal error at %s:%d: %s", __FILE__, __LINE__, str); \
        exit(-1);                                                             \
    } while (0);
#endif
#endif
