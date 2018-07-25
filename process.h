#ifndef RPROCESS_H
#define RPROCESS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "def.h"

    typedef int PID;

    typedef struct pid_status
    {
        PID pid;

    } PIDStatus;

    typedef enum
    {
        SIGNAL_CHILD
    } SignalType;

    typedef int SignalFlags; /* Set of signal flags for
                            program. See defines with
                            SignalFlags */

#define SF_RESTART                              \
    0x01 /* SignalFlags: Functions will not     \
            fail with EINTR if they would, they \
            will retry */

    typedef void (*SignalHandler)(int);

    PID ForkProcess(void);

    int SetSignalHandler(SignalType signum, SignalHandler Handler,
                         SignalFlags saFlags);

    PIDStatus GetPIDStatus(PID pid);
#ifdef __cplusplus
}
#endif
#endif
