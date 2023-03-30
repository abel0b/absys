#ifndef ABSYSTIME__H
#define ABSYSTIME__H

#include <stdint.h>
#include "absys/defs.h"

#if UNIX
#include <time.h>
#include <sys/time.h>
#else
#include <windows.h>
#endif

#if LINUX
#define ABSYS_TIMING_BACKEND_CLOCK_GETTIME
#endif

struct absys_timer {
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
    struct timespec start;
    struct timespec end;
#else
    struct timeval start;
    struct timeval end;
#endif
};

ABSYS_API void absys_timer_start(struct absys_timer* timer);
ABSYS_API long absys_timer_end(struct absys_timer* timer);
ABSYS_API double absys_get_wtime(void);
ABSYS_API uint64_t absys_time_get_us();

#endif
