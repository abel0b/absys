#ifndef ABLTIME__H
#define ABLTIME__H

#include <stdint.h>

#if UNIX
#include <sys/time.h>
#endif

#if WINDOWS
#include <windows.h>

struct timezone;

int gettimeofday(struct timeval* tp, struct timezone* tzp);
#endif

struct abl_timer {
    struct timeval start;
    struct timeval end;
};

void abl_timer_start(struct abl_timer* timer);
int abl_timer_end(struct abl_timer* timer);

int abl_time_get();
uint64_t abl_time_get_us();

#endif
