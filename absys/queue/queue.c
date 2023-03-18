#include "absys/queue.h"
#include <string.h>

absys_queue_impl(int, int)

ABSYS_API void absys_queue_new(struct absys_queue* queue, size_t elem_size) {
    queue->front = 0;
    queue->capacity = 8;
    queue->size = 0;
    queue->elem_size = elem_size;
    queue->data = absys_malloc(elem_size * queue->capacity);
}

ABSYS_API void absys_queue_del(struct absys_queue* queue) {
    if (queue->data) {
        absys_free(queue->data);
    }
}

ABSYS_API void absys_queue_reserve(struct absys_queue* queue, int newcap) {
    if (newcap > queue->capacity) {
        queue->capacity = newcap;
        queue->data = absys_realloc(queue->data, queue->capacity * queue->elem_size);
    }
}

ABSYS_API void absys_queue_enqueue(struct absys_queue* queue, void* elem) {
    if (queue->size == queue->capacity && queue->size) {
        int prev_cap = queue->capacity;
        queue->capacity *= 2;
        queue->data = absys_realloc(queue->data, queue->capacity * queue->elem_size);
        if (queue->front + queue->size > prev_cap) {
            memcpy((char*)queue->data + (prev_cap - 1) * queue->elem_size, queue->data, queue->elem_size);
        }
    }
    memcpy((char*)queue->data + queue->elem_size * ((queue->front + queue->size) % queue->capacity), elem, queue->elem_size);
    ++ queue->size;
}

ABSYS_API void absys_queue_dequeue(struct absys_queue* queue, void* elem) {
    -- queue->size;
    memcpy(elem, (char*)queue->data + queue->elem_size * queue->front, queue->elem_size);
    queue->front = (queue->front + 1) % queue->capacity;
}
