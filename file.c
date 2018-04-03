#include <libgen.h>

#include <stdlib.h>
#include <string.h>

/* File related includes */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sys/mman.h>

char *BaseName(char *restrict destBuf, const char *restrict pathstr)
{
    /* TODO: This function is doing a lot of unnecessary work. Do this simpler? */
    strcpy(destBuf, pathstr);
    return basename(destBuf);

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

    if(fileLength)
    {
	*fileLength = fileSize;
    }

    close(fd);

    return fileBuf;
}
