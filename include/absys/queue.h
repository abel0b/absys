#ifndef ABSYSqueue__H
#define ABSYSqueue__H

#include <stdlib.h>
#include <assert.h>
#include "absys/log.h"
#include "absys/mem.h"

struct absys_queue {
    void* data;
    int front;
    int size;
    int capacity;
    size_t elem_size;
};

ABSYS_API void absys_queue_new(struct absys_queue* queue, size_t elem_size);
ABSYS_API void absys_queue_del(struct absys_queue* queue);
ABSYS_API void absys_queue_reserve(struct absys_queue* queue, int newcap);
ABSYS_API void absys_queue_enqueue(struct absys_queue* queue, void* elem);
ABSYS_API void absys_queue_dequeue(struct absys_queue* queue, void* elem);

#define absys_queue_decl(TYPE, NAME) \
struct absys_queue_##NAME {\
    TYPE* data;\
    int front;\
    int size;\
    int capacity;\
};\
ABSYS_API void absys_queue_##NAME##_new(struct absys_queue_##NAME* queue);\
ABSYS_API void absys_queue_##NAME##_del(struct absys_queue_##NAME* queue);\
ABSYS_API void absys_queue_##NAME##_reserve(struct absys_queue_##NAME* queue, int newcap);\
ABSYS_API void absys_queue_##NAME##_enqueue(struct absys_queue_##NAME* queue, TYPE elem);\
ABSYS_API TYPE absys_queue_##NAME##_dequeue(struct absys_queue_##NAME* queue);\

#define absys_queue_impl(TYPE, NAME)\
ABSYS_API void absys_queue_##NAME##_new(struct absys_queue_##NAME* queue) {\
    queue->front = 0;\
    queue->capacity = 8;\
    queue->size = 0;\
    queue->data = absys_malloc(sizeof(TYPE) * queue->capacity);\
}\
ABSYS_API void absys_queue_##NAME##_del(struct absys_queue_##NAME* queue) {\
    if (queue->data) {\
        absys_free(queue->data);\
    }\
}\
ABSYS_API void absys_queue_##NAME##_reserve(struct absys_queue_##NAME* queue, int newcap) {\
    if (newcap > queue->capacity) {\
        queue->capacity = newcap;\
        queue->data = absys_realloc(queue->data, queue->capacity * sizeof(TYPE));\
    }\
}\
ABSYS_API void absys_queue_##NAME##_enqueue(struct absys_queue_##NAME* queue, TYPE elem) {\
    if (queue->capacity == queue->size) {\
        int prev_cap = queue->capacity;\
        absys_queue_##NAME##_reserve(queue, 2 * queue->capacity);\
        if (queue->front + queue->size > prev_cap) {\
            memcpy((char*)queue->data + (prev_cap - 1) * sizeof(TYPE), queue->data, sizeof(TYPE));\
        }\
    }\
   queue->data[queue->size] = elem;\
   ++ queue->size;\
}\
ABSYS_API TYPE absys_queue_##NAME##_dequeue(struct absys_queue_##NAME* queue) {\
    assert(queue->size > 0);\
    -- queue->size;\
    return queue->data[queue->size];\
}

absys_queue_decl(int, int)

#endif
