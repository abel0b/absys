#ifndef ABSYSOBJPOOL__H
#define ABSYSOBJPOOL__H

#include <stdlib.h>
#include "absys/vec.h"
#include "absys/defs.h"

struct absys_objpool_chunk {
    char* data;
    size_t cursor;
    size_t capacity;
};

struct absys_objpool {
    struct absys_objpool_chunk* chunks;
    int num_chunks;
    int cap_chunks;
    size_t elem_size;
    void (*del)(void*);
};

ABSYS_API void absys_objpool_new(struct absys_objpool* objpool, size_t elem_size, void del(void*));
ABSYS_API void absys_objpool_del(struct absys_objpool* objpool);
ABSYS_API void* absys_objpool_alloc(struct absys_objpool* objpool);
ABSYS_API void* absys_objpool_arralloc(struct absys_objpool* objpool, int n);
ABSYS_API void absys_objpool_pop(struct absys_objpool* objpool, int size);

#endif
