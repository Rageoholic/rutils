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

char *BaseName(char *restrict destBuf, isize destBufLen,
               const char *restrict pathstr, isize pathstrlen)
{
    if (pathstrlen == NO_GIVEN_LEN)
    {
        pathstrlen = (isize)strlen(pathstr);
    }
    isize baseStrIndex = 0;
    for (baseStrIndex = pathstrlen; baseStrIndex > 0; baseStrIndex--)
    {
        if (pathstr[baseStrIndex] == '/' || pathstr[baseStrIndex] == '\\')
        {
            baseStrIndex++;
            break;
        }
    }
    StrCpyAndLen(destBuf, &pathstr[baseStrIndex], (size_t)destBufLen);

    return destBuf;
}

char *MapFileToROBuffer(const char *filename, void *addrHint, isize *mappingSize)
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

    isize fileSize = st.st_size + 1;

    char *fileBuf = mmap(addrHint, (usize)fileSize, PROT_READ, MAP_PRIVATE, fd, 0);

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
