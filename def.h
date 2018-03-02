#ifndef RDEF_H
#define RDEF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef NDEBUG
#define DEBUG 1
#endif

/* Types and constants */

#define local static /* Function is local to the file */

#define ignore                                                                 \
  (void)/* Ignore this variable. Turns off warnings for unused                 \
           vars in functions that care */

typedef int ReadFlags; /* Set of flags for reading files. See
                          DEFINEs with ReadFlags */

#define READ_PEEK                                                              \
  0x01 /* ReadFlags: Don't actually advance                                    \
          the buffer */

#define READ_NO_BLOCK                                                          \
  0x02 /* ReadFlags: Don't block on reading                                    \
          data from the descriptor */

#endif
