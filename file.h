#ifndef RFILE_H
#define RFILE_H
#include "def.h"
#ifdef __cplusplus
extern "C"
{
#endif
    char *BaseName(char *restrict destBuf, ssize_t destBufLen,
                   const char *restrict pathstr, ssize_t pathstrlen);

    char *MapFileToROBuffer(const char *filename, void *addrHint, ssize_t *mappingSize);

    void UnmapMappedBuffer(void *buf, size_t len);
#ifdef __cplusplus
}
#endif
#endif
