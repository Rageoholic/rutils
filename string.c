/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "string.h"
#include "debug.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

size_t StrCpyAndLen(char *restrict dest, const char *restrict src, size_t destBufLen)
{
    if (destBufLen == 0)
    {
        return 0;
    }
    size_t i;
    for (i = 0; i < destBufLen - 1; i++)
    {
        if (!src[i])
        {
            break;
        }
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return i;
}

char **SplitLines(char *req)
{
    char **stringArr = calloc(10, sizeof(char *));
    size_t sizeofStringArr = 10;
    size_t stringArrIndex = 1;
    stringArr[0] = req;
    bool lastWasSplit = false;

    for (int i = 0; req[i] != '\0'; i++)
    {
        if (req[i] == '\r' || req[i] == '\n')
        {
            req[i] = '\0';
            lastWasSplit = true;
        }
        else if (lastWasSplit)
        {
            stringArr[stringArrIndex++] = req + i;
            lastWasSplit = false;
            if (stringArrIndex == sizeofStringArr)
            {
                sizeofStringArr *= 2;
                if ((stringArr = realloc(stringArr, sizeofStringArr)) == NULL)
                {
                    errno = ENOMEM;
                    return NULL;
                };
            }
        }
    }

    stringArr[stringArrIndex] = NULL;
    return stringArr;
}

bool StrStartsWith(char *string, char *subString, isize subStringLen)
{
    if (subStringLen == NO_GIVEN_LEN)
    {
        subStringLen = (isize)strlen(subString);
    }
    return !strncmp(string, subString, (usize)subStringLen);
}

bool StringEq(const char *str1, const char *str2)
{
    return !strcmp(str1, str2);
}

bool SubStringEq(const char *str1, const char *str2, size_t n)
{
    return !strncmp(str1, str2, n);
}
