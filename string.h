#ifndef STRING_H
#define STRING_H
#include "def.h"
#include "string.h"

bool StringStartsWith(char *string, char *subString, size_t subStringLen);

char **SplitLines(char *req);

/* Needs a better name */
int strcpyi(char *restrict dest, const char *restrict src, size_t maxdeststrlen);
#endif
