#define _XOPEN_SOURCE 1000

#include "process.h"

#include <signal.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

local int SignalTypeToSignal(SignalType sig)
{
    switch (sig)
    {
    case SIGNAL_CHILD:
        return SIGCHLD;
    }
    return -1;
}

local int SignalFlagsToSaFlags(SignalFlags sigType)
{
    int saFlags = 0;
    if (sigType && SF_RESTART)
    {
        saFlags |= SA_RESTART;
    }
    return saFlags;
}

int SetSignalHandler(SignalType signum, SignalHandler handler,
                     SignalFlags saFlags)
{
    struct sigaction sa = {.sa_handler = handler, .sa_flags = SignalFlagsToSaFlags(saFlags)};

    return sigaction(SignalTypeToSignal(signum), &sa, NULL);
}

PIDStatus GetPIDStatus(PID pid)
{
    int status;

    PID p;
    if ((p = waitpid(pid, &status, WNOHANG)) == 0)
    {
        // NOTE: Nothing happened to our process. Return NO_ACTION
    }
    PIDStatus stat = {0};

    stat.pid = p;
    return stat;
}

PID ForkProcess()
{
    return fork();
}
