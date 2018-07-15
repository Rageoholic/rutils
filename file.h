#ifndef RFILE_H
#define RFILE_H
#include "def.h"

char *BaseName(char *restrict destBuf, ssize_t destBufLen,
               const char *restrict pathstr, ssize_t pathstrlen);

char *MapFileToROBuffer(const char *filename, void *addrHint, ssize_t *fileLength);
#endif
