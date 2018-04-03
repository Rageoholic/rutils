#ifndef FILE_H
#define FILE_H

char *BaseName(char *restrict destBuf, const char *restrict pathstr);

char *MapFileToROBuffer(const char *filename, void *addrHint, size_t *fileLength);
#endif
