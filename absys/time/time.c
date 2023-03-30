#include "absys/time.h"
#include "absys/log.h"
#include <stdlib.h>


#if WINDOWS
#include <windows.h>
// credit: https://stackoverflow.com/a/26085827
int gettimeofday(struct timeval * tp, struct timezone * tzp) {
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}
#else
#include <sys/time.h>
#endif

ABSYS_API double absys_get_wtime( void ) {
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
    struct timespec ts;
    int rc = clock_gettime(CLOCK_REALTIME, &ts);
#else
    struct timeval tv;
    int rc = gettimeofday( &tv, NULL );
#endif
    if (rc != 0) {
        absys_elog("could not get time");
        exit(1);
    }
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
    double t = ts.tv_sec + ts.tv_nsec * 1.0e-9L;
#else
    double t = tv.tv_sec + tv.tv_usec * 1.0e-6L;
#endif
    return t;
}

ABSYS_API void absys_timer_start(struct absys_timer* timer) {
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
    int rc = clock_gettime(CLOCK_REALTIME, &timer->start);
#else
    int rc = gettimeofday(&timer->start, NULL);
#endif
    if (rc != 0) {
	exit(1);
    }
}

ABSYS_API long absys_timer_end(struct absys_timer* timer) { 
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
    int rc = clock_gettime(CLOCK_REALTIME, &timer->end);
#else
    int rc = gettimeofday(&timer->end, NULL);
#endif
    if (rc != 0) {
	    exit(1);
	}
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
    long time_us = (timer->end.tv_sec - timer->start.tv_sec) * 1e6 + (timer->end.tv_nsec - timer->start.tv_nsec) * 1e3;
#else
    long time_us = (timer->end.tv_sec - timer->start.tv_sec) * 1e6 + (timer->end.tv_usec - timer->start.tv_usec);
#endif
    return time_us;
}


ABSYS_API uint64_t absys_time_get_us() {
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
	struct timespec ts;
    	int rc = clock_gettime(CLOCK_REALTIME, &ts);
#else
	struct timeval tv;
	int rc = gettimeofday(&tv, NULL);
#endif
    if (rc != 0) {
        absys_elog("could not get time");
        exit(1);
     }
#ifdef ABSYS_TIMING_BACKEND_CLOCK_GETTIME
    return ts.tv_sec * 1e6 + ts.tv_nsec * 1e3;
#else
    return tv.tv_sec * 1e6 + tv.tv_usec;
#endif
}
