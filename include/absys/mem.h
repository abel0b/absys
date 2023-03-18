#ifndef ABSYSMEMORY__H
#define ABSYSMEMORY__H

#include <stdlib.h>
#include "absys/defs.h"

#if DEBUG
ABSYS_API void* absys_malloc_aux(size_t size, const char* file, int line, const char* func);
ABSYS_API void* absys_realloc_aux(void * ptr, size_t newsize, const char* file, int line, const char* func);
ABSYS_API void absys_free_aux(void * ptr, const char* file, int line, const char* func);
#define absys_malloc(SIZE) absys_malloc_aux(SIZE, __FILE__, __LINE__, __func__)
#define absys_realloc(PTR, SIZE)  absys_realloc_aux(PTR, SIZE, __FILE__, __LINE__, __func__)
#define absys_free(PTR) absys_free_aux(PTR, __FILE__, __LINE__, __func__)
#else
ABSYS_API void* absys_malloc_aux(size_t size);
ABSYS_API void* absys_realloc_aux(void * ptr, size_t newsize);
ABSYS_API void absys_free_aux(void * ptr);
#define absys_malloc absys_malloc_aux
#define absys_realloc absys_realloc_aux
#define absys_free absys_free_aux
#endif

#endif
