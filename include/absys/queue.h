#ifndef ABSYSqueue__H
#define ABSYSqueue__H

#include <stdlib.h>
#include <stdbool.h>
#include "absys/log.h"
#include "absys/mem.h"
#include "absys/utils.h"

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
struct absys_##NAME##_queue {\
    TYPE* data;\
    int front;\
    int size;\
    int capacity;\
};\
ABSYS_API void absys_##NAME##_queue_init(struct absys_##NAME##_queue * queue);\
ABSYS_API void absys_##NAME##_queue_exit(struct absys_##NAME##_queue * queue);\
ABSYS_API void absys_##NAME##_queue_reserve(struct absys_##NAME##_queue * queue, int newcap);\
ABSYS_API void absys_##NAME##_queue_enqueue(struct absys_##NAME##_queue * queue, TYPE elem);\
ABSYS_API TYPE absys_##NAME##_queue_dequeue(struct absys_##NAME##_queue * queue);\
ABSYS_API TYPE * absys_##NAME##_queue_tail(struct absys_##NAME##_queue * queue);\
ABSYS_API TYPE * absys_##NAME##_queue_head(struct absys_##NAME##_queue * queue);\
ABSYS_API bool absys_##NAME##_queue_empty(struct absys_##NAME##_queue * queue);\

#define absys_queue_impl(TYPE, NAME)\
ABSYS_API void absys_##NAME##_queue_init(struct absys_##NAME##_queue * queue) {\
    queue->front = 0;\
    queue->capacity = 8;\
    queue->size = 0;\
    queue->data = absys_malloc(sizeof(TYPE) * queue->capacity);\
}\
ABSYS_API void absys_##NAME##_queue_exit(struct absys_##NAME##_queue * queue) {\
    if (queue->data) {\
        absys_free(queue->data);\
    }\
}\
ABSYS_API bool absys_##NAME##_queue_empty(struct absys_##NAME##_queue * queue) {\
	return queue->size == 0;\
}\
ABSYS_API void absys_##NAME##_queue_reserve(struct absys_##NAME##_queue * queue, int newcap) {\
    if (newcap > queue->capacity) {\
        queue->capacity = newcap;\
        queue->data = absys_realloc(queue->data, queue->capacity * sizeof(TYPE));\
    }\
}\
ABSYS_API void absys_##NAME##_queue_enqueue(struct absys_##NAME##_queue * queue, TYPE elem) {\
    if (queue->capacity == queue->size) {\
        int prev_cap = queue->capacity;\
        absys_##NAME##_queue_reserve(queue, 2 * queue->capacity);\
        if (queue->front + queue->size > prev_cap) {\
            memcpy((char*)queue->data + (prev_cap - 1) * sizeof(TYPE), queue->data, sizeof(TYPE));\
        }\
    }\
   queue->data[queue->size] = elem;\
   ++ queue->size;\
}\
ABSYS_API TYPE absys_##NAME##_queue_dequeue(struct absys_##NAME##_queue * queue) {\
    absys_assert(queue->size > 0);\
    -- queue->size;\
    return queue->data[queue->size];\
}\
ABSYS_API TYPE * absys_##NAME##_queue_tail(struct absys_##NAME##_queue * queue) {\
    absys_assert(queue->size > 0);\
    return &queue->data[queue->size-1];\
}\
ABSYS_API TYPE * absys_##NAME##_queue_head(struct absys_##NAME##_queue * queue) {\
    absys_assert(queue->size > 0);\
    return &queue->data[0];\
}
absys_queue_decl(int, int)

#endif
