#include <libgen.h>

#include "string.h"
#include <stdlib.h>
#include <string.h>

/* File related includes */
#include "file.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/mman.h>

char *BaseName(char *restrict destBuf, ssize_t destBufLen,
               const char *restrict pathstr, ssize_t pathstrlen)
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
    StrCpyAndLen(destBuf, &pathstr[baseStrIndex], destBufLen);

    return destBuf;
}

char *MapFileToROBuffer(const char *filename, void *addrHint, ssize_t *mappingSize)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        return NULL;
    }

    struct stat st = {0};

    if (fstat(fd, &st) == -1)
    {
        return NULL;
    }

    ssize_t fileSize = st.st_size + 1;

    char *fileBuf = mmap(addrHint, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);

    if (mappingSize)
    {
        *mappingSize = fileSize;
    }

    close(fd);

    return fileBuf;
}

void UnmapMappedBuffer(void *buf, size_t len)
{
    munmap(buf, len);
}
