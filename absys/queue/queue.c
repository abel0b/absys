#include "absys/queue.h"

static void absys_queue_node_init(struct absys_queue_node* node, int elem_size) {
	node->size = 0;
	node->prev = node;
	node->next = node;
	node->data = absys_malloc(elem_size * ABSYS_QUEUE_UNROLL_FACTOR);
}

ABSYS_API void absys_queue_init(struct absys_queue* queue, size_t elem_size) {
	queue->size = 0;
	queue->elem_size = elem_size;
	absys_objpool_init(&queue->node_pool, sizeof(struct absys_queue_node), NULL);
	queue->head = absys_objpool_alloc(&queue->node_pool);
	queue->tail = queue->head;
	absys_queue_node_init(queue->head, queue->elem_size);
}

ABSYS_API void absys_queue_exit(struct absys_queue* queue) {
	absys_objpool_exit(&queue->node_pool);
}

ABSYS_API bool absys_queue_empty(struct absys_queue* queue) {
	return queue->size == 0;
}

ABSYS_API int absys_queue_size(struct absys_queue* queue) {
	return queue->size;
}

ABSYS_API void* absys_queue_peek(struct absys_queue* queue) {
	return queue->head->data;
}

void _absys_queue_add(struct absys_queue* queue, struct absys_queue_node* node, int offset, void * value) {
	if (node->size == ABSYS_QUEUE_UNROLL_FACTOR) {
		struct absys_queue_node * new_node = (struct absys_queue_node*) absys_objpool_alloc(&queue->node_pool);
		absys_queue_node_init(new_node, queue->elem_size);
		new_node->prev = node;
		new_node->next = node->next;
		node->next = new_node;
		new_node->next->prev = new_node;
	
		if (queue->tail == node) {
			queue->tail = new_node;
		}

		if (offset == ABSYS_QUEUE_UNROLL_FACTOR) {
			memcpy(new_node->data, value, queue->elem_size);
			new_node->size = 1;
			queue->size++;
			return;
		}
	}

	void* value_store = node->data + queue->elem_size * offset;
	if (offset < node->size) {
		memmove(value_store + queue->elem_size, value_store, queue->elem_size * (node->size - offset));
	}
	queue->size++;
	memcpy(value_store, value, queue->elem_size);
	++ node->size;
}

void _absys_queue_rem(struct absys_queue* queue, struct absys_queue_node* node, int offset) {
	void* value_store = node->data + queue->elem_size * offset;
	if (offset < node->size - 1) {
		memmove(value_store, value_store + queue->elem_size, queue->elem_size * (node->size - offset - 1));
	}
	-- queue->size;
	-- node->size;

	if (node->size == 0) {
		if (node == queue->head && queue->size != 0) {
			queue->head = node->next;
			node->next->prev = queue->tail;
			queue->tail->next = queue->head;
		}
		else if (node == queue->tail) {
			queue->tail = node->prev;
			node->prev->next = queue->head;
			queue->head->prev = queue->tail;
		}
		else {
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		absys_objpool_free(&queue->node_pool, node);
	}
}

ABSYS_API void absys_queue_enqueue(struct absys_queue* queue, void* elem) {
	_absys_queue_add(queue, queue->tail, queue->tail->size, elem);
}

ABSYS_API void absys_queue_dequeue(struct absys_queue* queue, void* elem) {
	void* value_store = queue->head->data;
	memcpy(elem, value_store, queue->elem_size);
	_absys_queue_rem(queue, queue->head, 0);
}

ABSYS_API void absys_int_queue_show(struct absys_queue* queue) {
	int ii = 0;
	struct absys_queue_node* node = queue->head;
	printf("queue");
	while(ii < queue->size) {
		printf(" -> [");
		for (int jj = 0; jj < node->size; ++jj) {
			printf("%d", *(int*)(node->data + jj * queue->elem_size));
			if (jj != node->size - 1) {
				printf(" ");
			}
		}
		printf("]");

		ii += node->size;
		node = node->next;
	}
	printf("\n");
}
