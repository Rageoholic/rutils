#ifndef RFILE_H
#define RFILE_H
#include "def.h"
#ifdef __cplusplus
extern "C"
{
#endif
    /*
       func: BaseName

       Takes a path and fills out destBuf with the base name of the path

       args

       destBuf: buffer to fill out

       destBufLen: length of buffer to fill out. If lower than needed size the
       basename is truncated

       pathstr: path string to be looked at

       pathstrlen: the length of the path string. Pass NO_GIVEN_LEN and it will
       be determined at runtime, but this hint makes things a little faster

     */
    char *BaseName(char *restrict destBuf, isize destBufLen,
                   const char *restrict pathstr, isize pathstrlen);

    /*
       func: MapFileToROBuffer

       Take a file path and create a read only mapping with the contents of that
       file. The contents are null terminated so you can use it as a C string.
       On error returns NULL.

       args

       filename: file to map

       addrHint: Hint as to where you want your address. It's not guaranteed to
       be accurate but hey you play with fire if you feel like it.

       mappingSize: Out parameter for the size of the mapping. You need this to
       undo the mapping.
     */

    char *MapFileToROBuffer(const char *filename, void *addrHint, isize *mappingSize);

    /*
      func: UnmapMappedBuffer

      Takes a mapping from this file and undos it. Acts as a destructor

      args

      buf: buffer to unmap. Must be gotten from a Map* function in this library.

      len: length of the buffer to be unmapped
     */
    void UnmapMappedBuffer(void *buf, size_t len);
#ifdef __cplusplus
}
#endif
#endif
