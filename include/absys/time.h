#ifndef ABSYSTIME__H
#define ABSYSTIME__H

#include <stdint.h>
#include "absys/defs.h"

#if UNIX
#include <sys/time.h>
#else
#include <windows.h>
#endif

struct absys_timer {
    struct timeval start;
    struct timeval end;
};

ABSYS_API void absys_timer_start(struct absys_timer* timer);
ABSYS_API int absys_timer_end(struct absys_timer* timer);

ABSYS_API double absys_get_wtime(void);
ABSYS_API int absys_time_get();
ABSYS_API uint64_t absys_time_get_us();

#endif
