#include "string.h"
#include "debug.h"

#include <stdlib.h>
#include <string.h>

size_t StringLen(String *s)
{
    return s->len;
}

/* TODO: This needs a *way* better name. I mean seriously */
int strcpyi(char *restrict dest, const char *restrict src, size_t maxdeststrlen)
{
    size_t i;
    for (i = 0; i < maxdeststrlen; i++)
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

String *CreateString(char *cstr)
{
    size_t len = strlen(cstr);
    String *str = malloc(sizeof(String) + len + 1);
    if (str == NULL)
    {
        return NULL;
    }

    str->len = len;
    strcpy(str->str, cstr);

    return str;
}

String *CreateStringEx(char *cstr, String *str, size_t len)
{
    assert(str != NULL); /* UB. Officially not my fucking
			    problem */
    size_t l = strcpyi(str->str, cstr, len);

    str->len = l;

    return str;
}

void DestroyString(String *str)
{
    free(str);
}
