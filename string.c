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

bool StrStartsWith(char *string, char *subString, size_t subStringLen)
{
    if (subStringLen == NO_GIVEN_LEN)
    {
        subStringLen = strlen(subString);
    }
    return !strncmp(string, subString, subStringLen);
}

bool streq(char *str1, char *str2)
{
    return !strcmp(str1, str2);
}

bool strneq(char *str1, char *str2, size_t n)
{
    return !strncmp(str1, str2, n);
}
