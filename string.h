#ifndef STRING_H
#define STRING_H
#include "def.h"
#include "string.h"

typedef char *CStr;

typedef struct ru_str
{
    size_t len;
    size_t capacity;
    char str[];
} String;

/* Accessors */

size_t StringLen(String *s);

/* Constructors */

String *CreateString(char *cstr);

String *InitString(char *cstr, String *str);

void DestroyString(String *str);

/* Needs a better name */
int strcpyi(char *restrict dest, const char *restrict src, size_t maxdeststrlen);
#endif
