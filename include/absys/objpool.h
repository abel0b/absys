#ifndef ABSYSOBJPOOL__H
#define ABSYSOBJPOOL__H

#include <stdlib.h>
#include "absys/vec.h"
#include "absys/defs.h"

#define ABSYS_OBJPOOL_CHUNK_SIZE 16384

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

#define absys_objpool_decl(TYPE, NAME) \
struct absys_##NAME##_objpool_chunk {\
    TYPE* data;\
    size_t cursor;\
    size_t capacity;\
};\
struct absys_##NAME##_objpool {\
    struct absys_##NAME##_objpool_chunk* chunks;\
    int num_chunks;\
    int cap_chunks;\
    size_t elem_size;\
    void (*del)(void*);\
};\
ABSYS_API void absys_##NAME##_objpool_new(struct absys_##NAME##_objpool* objpool);\
ABSYS_API void absys_##NAME##_objpool_del(struct absys_##NAME##_objpool* objpool);\
ABSYS_API void* absys_##NAME##_objpool_alloc(struct absys_##NAME##_objpool* objpool);\
ABSYS_API void* absys_##NAME##_objpool_arralloc(struct absys_##NAME##_objpool* objpool, int n);\
ABSYS_API void absys_##NAME##_objpool_pop(struct absys_##NAME##_objpool* objpool, int size);

#define absys_objpool_impl(TYPE, NAME) \
static void absys_##NAME##_objpool_chunk_new(struct absys_##NAME##_objpool_chunk* chunk) {\
    chunk->capacity = ABSYS_OBJPOOL_CHUNK_SIZE;\
    chunk->cursor = 0;\
    chunk->data = absys_malloc(chunk->capacity);\
}\
static void absys_##NAME##_objpool_chunk_del(struct absys_##NAME##_objpool_chunk* chunk) {\
    absys_free(chunk->data);\
}\
ABSYS_API void absys_##NAME##_objpool_new(struct absys_##NAME##_objpool* objpool, size_t elem_size, void del(void*)) {\
    absys_assert(sizeof(TYPE) < ABSYS_OBJPOOL_CHUNK_SIZE);\
    objpool->cap_chunks = 1;\
    objpool->num_chunks = 1;\
    objpool->chunks = absys_malloc(sizeof(struct absys_##NAME##_objpool_chunk));\
    absys_##NAME##_objpool_chunk_new(&objpool->chunks[0]);\
}\
ABSYS_API void absys_##NAME##_objpool_del(struct absys_##NAME##_objpool* objpool) {\
    if (objpool->cap_chunks) {\
        for(int i = 0; i < objpool->num_chunks; ++i) {\
            absys_##NAME##_objpool_chunk_del(&objpool->chunks[i]);\
        }\
        absys_free(objpool->chunks);\
    }\
}\
ABSYS_API void* absys_##NAME##_objpool_alloc(struct absys_##NAME##_objpool* objpool) {\
    int chunk = objpool->num_chunks - 1;\
    if (sizeof(TYPE) > ABSYS_OBJPOOL_CHUNK_SIZE - objpool->chunks[chunk].cursor) {\
        if (objpool->cap_chunks == objpool->num_chunks) {\
            objpool->cap_chunks *= 2;\
            objpool->chunks = (struct absys_##NAME##_objpool_chunk*) absys_realloc(objpool->chunks, objpool->cap_chunks * sizeof(struct absys_##NAME##_objpool_chunk));\
        }\
        ++ chunk;\
        ++ objpool->num_chunks;\
        absys_##NAME##_objpool_chunk_new(&objpool->chunks[chunk]);\
    }\
    void* obj = (void*) (objpool->chunks[chunk].data + objpool->chunks[chunk].cursor);\
    objpool->chunks[chunk].cursor += sizeof(TYPE);\
    return obj;\
}\
ABSYS_API void* absys_##NAME##_objpool_arralloc(struct absys_##NAME##_objpool* objpool, int count) {\
    absys_assert(count * sizeof(TYPE) < ABSYS_OBJPOOL_CHUNK_SIZE);\
    int chunk = objpool->num_chunks - 1;\
    if (sizeof(TYPE) * count > ABSYS_OBJPOOL_CHUNK_SIZE - objpool->chunks[chunk].cursor) {\
        if (objpool->cap_chunks == objpool->num_chunks) {\
            objpool->cap_chunks *= 2;\
            objpool->chunks = (struct absys_##NAME##_objpool_chunk*) absys_realloc(objpool->chunks, objpool->cap_chunks * sizeof(struct absys_##NAME##_objpool_chunk));\
        }\
        ++ chunk;\
        ++ objpool->num_chunks;\
        absys_##NAME##_objpool_chunk_new(&objpool->chunks[chunk]);\
    }\
    void* obj = (void*) (objpool->chunks[chunk].data + objpool->chunks[chunk].cursor);\
    objpool->chunks[chunk].cursor += count * sizeof(TYPE);\
    return obj;\
}\
ABSYS_API void absys_##NAME##_objpool_pop(struct absys_##NAME##_objpool* objpool, int count) {\
    int chunk = objpool->num_chunks - 1;\
    absys_assert((size_t)objpool->chunks[chunk].cursor >= count * sizeof(TYPE));\
    objpool->chunks[chunk].cursor -= count * sizeof(TYPE);\
    if (objpool->chunks[chunk].cursor == 0 && objpool->num_chunks > 1) {\
        -- objpool->num_chunks;\
    }\
}

#endif
