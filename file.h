#ifndef RFILE_H
#define RFILE_H
#include "def.h"

char *BaseName(char *restrict destBuf, size_t destBufLen,
               const char *restrict pathstr, size_t pathstrlen);

char *MapFileToROBuffer(const char *filename, void *addrHint, size_t *fileLength);
#endif
