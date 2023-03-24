#ifndef __DEBUG_UTILS_h
#define __DEBUG_UTILS_h

#include "debugbreak.h"
#include <stdlib.h>
#include "absys/log.h"
#if DEBUG_SAN
#include <sanitizer/common_interface_defs.h>
#endif

#if WINDOWS
#define DS '\\'
#else
#define DS '/'
#endif

#ifdef WINDOWS
#define UNIX !WINDOWS
#else
#define UNIX 1
#endif

#define absys_assert(cond) if (!(cond)) { fprintf(stderr, "assertion failed at %s:%d: %s\n", __FILE__, __LINE__, #cond); debug_break(); }

#define absys_todo(...) do { absys_elog("TODO feature at %s:%s:%d", __FILE__, __func__, __LINE__); absys_elog(__VA_ARGS__); exit(1); } while(0)

#define absys_unused(X) do { (void)(X); } while(0)

#if DEBUG_SAN
#define absys_exit(X) do {if (X) {__sanitizer_print_stack_trace(); exit(X);}else{exit(X);}} while(0)
#else
#define absys_exit(X) exit(X)
#endif


#endif
