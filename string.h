#ifndef STRING_H
#define STRING_H
#include "def.h"
#include <string.h>

bool StrStartsWith(char *string, char *subString, size_t subStringLen);

char **SplitLines(char *req);

/* Needs a better name */
int strcpyi(char *restrict dest, const char *restrict src, size_t maxdeststrlen);

bool streq(char *str1, char *str2);
bool strneq(char *str1, char *str2, size_t n);

int StrCpyAndLen(char *restrict dest, const char *restrict src, size_t maxdeststrlen);

#endif
