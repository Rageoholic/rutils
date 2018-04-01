#include <libgen.h>

#include <stdlib.h>
#include <string.h>

char *BaseName(char *restrict destBuf, const char *restrict pathstr)
{
    /* TODO: This function is doing a lot of unnecessary work. Do this simpler? */
    strcpy(destBuf, pathstr);
    return basename(destBuf);

}
