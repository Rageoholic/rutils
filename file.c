#include <libgen.h>

#include <stdlib.h>
#include <string.h>

/* File related includes */
#include "file.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/mman.h>

char *BaseName(char *restrict destBuf, size_t destBufLen,
               const char *restrict pathstr, size_t pathstrlen)
{
    if (pathstrlen == NO_GIVEN_LEN)
    {
        pathstrlen = strlen(pathstr);
    }
    int baseStrIndex = 0;
    for (baseStrIndex = pathstrlen; baseStrIndex > 0; baseStrIndex--)
    {
        if (pathstr[baseStrIndex] == '/' || pathstr[baseStrIndex] == '\\')
        {
            baseStrIndex++;
            break;
        }
    }

    if (destBufLen > 0)
    {
        strncpy(destBuf, &pathstr[baseStrIndex], destBufLen - 1);
        destBuf[destBufLen - 1] = '\0';
    }
    return destBuf;
}

char *MapFileToROBuffer(const char *filename, void *addrHint, size_t *fileLength)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        return NULL;
    }

    struct stat st = {};

    if (fstat(fd, &st) == -1)
    {
        return NULL;
    }

    size_t fileSize = st.st_size;

    char *fileBuf = mmap(addrHint, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);

    if (fileLength)
    {
        *fileLength = fileSize;
    }

    close(fd);

    return fileBuf;
}
