/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef RDEBUG_H
#define RDEBUG_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR(str)                                                              \
    do                                                                          \
    {                                                                           \
        fprintf(stderr, "fatal error at %s:%d: %s\n", __FILE__, __LINE__, str); \
        abort();                                                                \
    } while (0);

#define INVARIANT(expr, str)                                            \
    do                                                                  \
    {                                                                   \
        if (!(expr))                                                    \
        {                                                               \
            fprintf(stderr, "Invariant violated at %s:%d: %s\n",        \
                    __FILE__, __LINE__, str);                           \
            abort();                                                    \
        }                                                               \
    } while (0)
#endif

