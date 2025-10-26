#ifndef __ABSYS_QUEUE_h
#define __ABSYS_QUEUE_h

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

ABSYS_API void absys_queue_init(struct absys_queue* queue, size_t elem_size);
ABSYS_API void absys_queue_exit(struct absys_queue* queue);
ABSYS_API int absys_queue_size(struct absys_queue* queue);
ABSYS_API bool absys_queue_empty(struct absys_queue* queue);
ABSYS_API void absys_queue_enqueue(struct absys_queue* queue, void* elem);
ABSYS_API void absys_queue_dequeue(struct absys_queue* queue, void* elem);
ABSYS_API void* absys_queue_peek(struct absys_queue* queue);
ABSYS_API void absys_int_queue_show(struct absys_queue* queue);

#define absys_queue_t(name) struct absys_##name##_queue 

#define absys_queue_decl_aux(TYPE, NAME, QUAL) \
struct absys_##NAME##_queue_node {\
	int size;\
	TYPE* data;\
	struct absys_##NAME##_queue_node * prev;\
	struct absys_##NAME##_queue_node * next;\
};\
struct absys_##NAME##_queue {\
    int size;\
	struct absys_##NAME##_queue_node* head;\
	struct absys_##NAME##_queue_node* tail;\
	struct absys_objpool node_pool;\
};\
ABSYS_API void absys_##NAME##_queue_init(struct absys_##NAME##_queue* queue);\
ABSYS_API void absys_##NAME##_queue_exit(struct absys_##NAME##_queue* queue);\
ABSYS_API bool absys_##NAME##_queue_empty(struct absys_##NAME##_queue* queue);\
ABSYS_API int absys_##NAME##_queue_size(struct absys_##NAME##_queue* queue);\
ABSYS_API TYPE* absys_##NAME##_queue_peek(struct absys_##NAME##_queue* queue);\
ABSYS_API void absys_##NAME##_queue_enqueue(struct absys_##NAME##_queue* queue, QUAL TYPE elem);\
ABSYS_API TYPE absys_##NAME##_queue_dequeue(struct absys_##NAME##_queue* queue);

#define absys_queue_decl(TYPE, NAME) absys_queue_decl_aux(TYPE,NAME,const)
#define absys_ptr_queue_decl(TYPE, NAME) absys_queue_decl_aux(TYPE,NAME,)


#define absys_queue_impl_aux(TYPE, NAME, QUAL)\
static void absys_##NAME##_queue_node_init(struct absys_##NAME##_queue_node* node) {\
	node->size = 0;\
	node->prev = node;\
	node->next = node;\
	node->data = absys_malloc(sizeof(TYPE) * ABSYS_QUEUE_UNROLL_FACTOR);\
}\
\
ABSYS_API void absys_##NAME##_queue_init(struct absys_##NAME##_queue* queue) {\
	queue->size = 0;\
	absys_objpool_init(&queue->node_pool, sizeof(struct absys_##NAME##_queue_node), NULL);\
	queue->head = absys_objpool_alloc(&queue->node_pool);\
	queue->tail = queue->head;\
	absys_##NAME##_queue_node_init(queue->head);\
}\
\
ABSYS_API void absys_##NAME##_queue_exit(struct absys_##NAME##_queue* queue) {\
	struct absys_##NAME##_queue_node* node = queue->head;\
	do {\
		struct absys_##NAME##_queue_node* next = node->next;\
		absys_free(node->data);\
		node = next;\
	} while (node != queue->head);\
	absys_objpool_exit(&queue->node_pool);\
}\
\
ABSYS_API bool absys_##NAME##_queue_empty(struct absys_##NAME##_queue* queue) {\
	return queue->size == 0;\
}\
\
ABSYS_API int absys_##NAME##_queue_size(struct absys_##NAME##_queue* queue) {\
	return queue->size;\
}\
\
ABSYS_API TYPE* absys_##NAME##_queue_peek(struct absys_##NAME##_queue* queue) {\
	return &queue->head->data[0];\
}\
\
void _absys_##NAME##_queue_add(struct absys_##NAME##_queue* queue, struct absys_##NAME##_queue_node* node, int offset, QUAL TYPE * value) {\
	if (node->size == ABSYS_QUEUE_UNROLL_FACTOR) {\
		struct absys_##NAME##_queue_node * new_node = (struct absys_##NAME##_queue_node*) absys_objpool_alloc(&queue->node_pool);\
		absys_##NAME##_queue_node_init(new_node);\
		new_node->prev = node;\
		new_node->next = node->next;\
		node->next = new_node;\
		new_node->next->prev = new_node;\
\
		if (queue->tail == node) {\
			queue->tail = new_node;\
		}\
\
		if (offset == ABSYS_QUEUE_UNROLL_FACTOR) {\
			new_node->data[0] = *value;\
			new_node->size = 1;\
			queue->size++;\
			return;\
		}\
	}\
\
	if (offset < node->size) {\
		for (int i = node->size; i > offset; --i) {\
			node->data[i] = node->data[i - 1];\
		}\
	}\
	node->data[offset] = *value;\
	++ queue->size;\
	++ node->size;\
}\
\
void _absys_##NAME##_queue_rem(struct absys_##NAME##_queue* queue, struct absys_##NAME##_queue_node* node, int offset) {\
	if (offset < node->size - 1) {\
		for (int i = offset; i < node->size - 1; ++i) {\
			node->data[i] = node->data[i + 1];\
		}\
	}\
	-- queue->size;\
	-- node->size;\
\
	if (node->size == 0) {\
		if (node == queue->head && queue->size != 0) {\
			queue->head = node->next;\
			node->next->prev = queue->tail;\
			queue->tail->next = queue->head;\
		}\
		else if (node == queue->tail) {\
			queue->tail = node->prev;\
			node->prev->next = queue->head;\
			queue->head->prev = queue->tail;\
		}\
		else {\
			node->prev->next = node->next;\
			node->next->prev = node->prev;\
		}\
		absys_objpool_free(&queue->node_pool, node);\
	}\
}\
\
ABSYS_API void absys_##NAME##_queue_enqueue(struct absys_##NAME##_queue* queue, QUAL TYPE elem) {\
	_absys_##NAME##_queue_add(queue, queue->tail, queue->tail->size, &elem);\
}\
\
ABSYS_API TYPE absys_##NAME##_queue_dequeue(struct absys_##NAME##_queue* queue) {\
	TYPE ret = queue->head->data[0];\
	_absys_##NAME##_queue_rem(queue, queue->head, 0);\
	return ret;\
}

#define absys_queue_impl(TYPE, NAME) absys_queue_impl_aux(TYPE,NAME,const)
#define absys_ptr_queue_impl(TYPE, NAME) absys_queue_impl_aux(TYPE,NAME,)

#endif
