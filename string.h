#ifndef STRING_H
#define STRING_H
#include "def.h"

typedef struct ru_str
{
    size_t len;
    char str[];
} String;

/* Accessors */

size_t StringLen(String *s);

/* Constructors */

String *CreateString(char *cstr);

String *CreateStringEx(char *cstr, String *str, size_t len);

void DestroyString(String *str);

#endif
