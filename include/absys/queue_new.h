#ifndef __ABSYS_LIST_h
#define __ABSYS_LIST_h

#include <stdbool.h>
#include "config.h"
#include "absys/objpool.h"

struct absys_queue_node {
	int size;
	void* data;
	struct absys_queue_node * prev;
	struct absys_queue_node * next;
};

struct absys_queue {
    int size;
    struct absys_queue_node* head;
    struct absys_queue_node* tail;
	size_t elem_size;
    struct absys_objpool node_pool;
};

struct absys_queue_it {
	struct absys_queue* queue;
	struct absys_queue_node* node;
	int cursor;
};

ABSYS_API void absys_queue_init(struct absys_queue* queue, size_t elem_size);
ABSYS_API void absys_queue_exit(struct absys_queue* queue);
ABSYS_API int absys_queue_size(struct absys_queue* queue);
ABSYS_API bool absys_queue_empty(struct absys_queue* queue);
ABSYS_API void* absys_queue_get(struct absys_queue* queue, int idx);
ABSYS_API void* absys_queue_head(struct absys_queue* queue);
ABSYS_API void absys_queue_enqueue(struct absys_queue* queue, void* elem);
ABSYS_API void absys_queue_dequeue(struct absys_queue* queue, void* elem);
ABSYS_API void absys_queue_it_init(struct absys_queue_it* iter, struct absys_queue* queue);
ABSYS_API void absys_queue_it_exit(struct absys_queue_it* iter);
ABSYS_API void absys_queue_it_get(struct absys_queue_it* iter, void* value);
ABSYS_API bool absys_queue_it_next(struct absys_queue_it* iter);



#define absys_queue_t(name) struct absys_##name##_queue 

#define absys_queue_decl_aux(TYPE, NAME, QUAL) \
struct absys_##NAME##_queue {\
    TYPE* data;\
    int size;\
    int capacity;\
};\
struct absys_##NAME##_queue_it {\
    int cursor;\
    struct absys_##NAME##_queue * queue;\
};\
ABSYS_API void absys_##NAME##_queue_init(struct absys_##NAME##_queue* queue);\
ABSYS_API void absys_##NAME##_queue_exit(struct absys_##NAME##_queue* queue);\
ABSYS_API bool absys_##NAME##_queue_empty(struct absys_##NAME##_queue* queue);\
ABSYS_API int absys_##NAME##_queue_size(struct absys_##NAME##_queue* queue);\
ABSYS_API TYPE absys_##NAME##_queue_get(struct absys_##NAME##_queue* queue, int idx);\
ABSYS_API TYPE absys_##NAME##_queue_head(struct absys_##NAME##_queue* queue, int idx);\
ABSYS_API TYPE absys_##NAME##_queue_tail(struct absys_##NAME##_queue* queue, int idx);\
ABSYS_APIvoid absys_##NAME##_queue_enqueue(struct absys_##NAME##_queue* queue, QUAL TYPE elem);\
ABSYS_API void absys_##NAME##_queue_dequeue(struct absys_##NAME##_queue* queue, TYPE* elem);\
ABSYS_API void absys_##NAME##_queue_it_init(struct absys_##NAME##_queue_it* iter, struct absys_##NAME##_queue* queue);\
ABSYS_API void absys_##NAME##_queue_it_exit(struct absys_##NAME##_queue_it* iter);\
ABSYS_API void absys_##NAME##_queue_it_get(struct absys_##NAME##_queue_it* iter, TYPE* value);\
ABSYS_API bool absys_##NAME##_queue_it_next(struct absys_##NAME##_queue_it* iter);

#define absys_queue_decl(TYPE, NAME) absys_queue_decl_aux(TYPE,NAME,const)
#define absys_ptr_queue_decl(TYPE, NAME) absys_queue_decl_aux(TYPE,NAME,)

#endif
