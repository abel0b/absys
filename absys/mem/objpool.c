#include "absys/objpool.h"
#include "absys/mem.h"
#include <assert.h>

static const size_t CHUNK_SIZE = 16384;

static void absys_objpool_chunk_new(struct absys_objpool_chunk* chunk) {
    chunk->capacity = CHUNK_SIZE;
    chunk->cursor = 0;
    chunk->data = (char*)absys_malloc(chunk->capacity);
}

static void absys_objpool_chunk_del(struct absys_objpool_chunk* chunk, size_t elem_size, void del(void*)) {
    if (del) {
        for(size_t i = 0; i * elem_size < (size_t)chunk->cursor; i++) {
            del((void*)&chunk->data[i * elem_size]);
        }
    }
    absys_free(chunk->data);
}

ABSYS_API void absys_objpool_new(struct absys_objpool* objpool, size_t elem_size, void del(void*)) {
    assert(elem_size < CHUNK_SIZE);
    objpool->cap_chunks = 1;
    objpool->num_chunks = 1;
    objpool->elem_size = elem_size;
    objpool->chunks = absys_malloc(sizeof(struct absys_objpool_chunk));
    absys_objpool_chunk_new(&objpool->chunks[0]);
    objpool->del = del;
}

ABSYS_API void absys_objpool_del(struct absys_objpool* objpool) {
    if (objpool->cap_chunks) {
        for(int i = 0; i < objpool->num_chunks; ++i) {
            absys_objpool_chunk_del(&objpool->chunks[i], objpool->elem_size, objpool->del);
        }
        absys_free(objpool->chunks);
    }
}

ABSYS_API void* absys_objpool_alloc(struct absys_objpool* objpool) {
    int chunk = objpool->num_chunks - 1;
    if (objpool->elem_size > CHUNK_SIZE - objpool->chunks[chunk].cursor) {
        if (objpool->cap_chunks == objpool->num_chunks) {
            objpool->cap_chunks *= 2;
            objpool->chunks = (struct absys_objpool_chunk*) absys_realloc(objpool->chunks, objpool->cap_chunks * sizeof(struct absys_objpool_chunk));
        }
        ++ chunk;
        ++ objpool->num_chunks;
        absys_objpool_chunk_new(&objpool->chunks[chunk]);
    }

    void* obj = (void*) (objpool->chunks[chunk].data + objpool->chunks[chunk].cursor);
    objpool->chunks[chunk].cursor += objpool->elem_size;
    return obj;
}

ABSYS_API void* absys_objpool_arralloc(struct absys_objpool* objpool, int count) {
    assert(count * objpool->elem_size < CHUNK_SIZE);
    int chunk = objpool->num_chunks - 1;
    if (objpool->elem_size * count > CHUNK_SIZE - objpool->chunks[chunk].cursor) {
        if (objpool->cap_chunks == objpool->num_chunks) {
            objpool->cap_chunks *= 2;
            objpool->chunks = (struct absys_objpool_chunk*) absys_realloc(objpool->chunks, objpool->cap_chunks * sizeof(struct absys_objpool_chunk));
        }
        ++ chunk;
        ++ objpool->num_chunks;
        absys_objpool_chunk_new(&objpool->chunks[chunk]);
    }

    void* obj = (void*) (objpool->chunks[chunk].data + objpool->chunks[chunk].cursor);
    objpool->chunks[chunk].cursor += count * objpool->elem_size;
    return obj;
}

ABSYS_API void absys_objpool_pop(struct absys_objpool* objpool, int count) {
    int chunk = objpool->num_chunks - 1;
    assert((size_t)objpool->chunks[chunk].cursor >= count* objpool->elem_size);
    objpool->chunks[chunk].cursor -= count * objpool->elem_size;
    if (objpool->chunks[chunk].cursor == 0 && objpool->num_chunks > 1) {
        -- objpool->num_chunks;
    }
}
