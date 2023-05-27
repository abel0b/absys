#include "absys/list.h"

static void absys_list_node_init(struct absys_list_node* node, int elem_size) {
	node->size = 0;
	node->prev = node;
	node->next = node;
	node->data = malloc(elem_size * ABSYS_LIST_UNROLL_FACTOR);
}

ABSYS_API void absys_list_init(struct absys_list* list, size_t elem_size) {
	list->size = 0;
	list->elem_size = elem_size;
	absys_objpool_init(&list->node_pool, sizeof(struct absys_list_node), NULL);
	list->head = absys_objpool_alloc(&list->node_pool);
	list->tail = list->head;
	absys_list_node_init(list->head, list->elem_size);
}

ABSYS_API void absys_list_exit(struct absys_list* list) {
	absys_objpool_exit(&list->node_pool);
}

ABSYS_API bool absys_list_empty(struct absys_list* list) {
	return (list->head == list->head->next) && !list->head->size;
}

ABSYS_API int absys_list_size(struct absys_list* list) {
	return list->size;
}

ABSYS_API void* absys_list_get(struct absys_list* list, int idx) {
	int ii = 0;
	struct absys_list_node* node = list->head;
	while(ii + node->size < idx) {
		// TODO: if (node == NULL) out_of_bound
		ii += node->size;
		node = node->next;
	}
	return &node->data[(idx - ii) * list->elem_size];
}

ABSYS_API void* absys_list_head(struct absys_list* list) {
	return list->head->data;
}

ABSYS_API void* absys_list_tail(struct absys_list* list) {
	return &list->tail->data[(list->tail->size - 1) * list->elem_size];
}

void _absys_list_add(struct absys_list* list, struct absys_list_node* node, int offset, void * value) {
	if (node->size == ABSYS_LIST_UNROLL_FACTOR) {
		struct absys_list_node * new_node = (struct absys_list_node*) absys_objpool_alloc(&list->node_pool);
		new_node->size = 0;
		new_node->prev = node;
		new_node->next = node->next;
		node->next = new_node;
		new_node->next->prev = new_node;
	
		if (offset == ABSYS_LIST_UNROLL_FACTOR - 1) {
			memcpy(new_node->data, value, list->elem_size);
			new_node->size = 1;
			return;
		}
	}

	void* value_store = node->data + list->elem_size * offset;
	if (offset < node->size) {
		memmove(value_store + list->elem_size, value_store, list->elem_size * (node->size - offset));
	}
	else {
		list->size++;
	}
	memcpy(value_store, value, list->elem_size);
	++ node->size;
}

void _absys_list_rem(struct absys_list* list, struct absys_list_node* node, int offset) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	// TODO: objpool dealloc
	void* value_store = node->data + list->elem_size * offset;
	if (offset < node->size) {
		memmove(value_store, value_store + list->elem_size, list->elem_size * (node->size - offset));
	}
	-- list->size;
	-- node->size;
}

ABSYS_API void absys_list_insert(struct absys_list* list, int idx, void* value) {
	int ii = 0;
	struct absys_list_node* node = list->head;
	while(ii + node->size < idx) {
		ii += node->size;
		node = node->next;
	}
	_absys_list_add(list, node, idx - ii, value);
}

ABSYS_API void absys_list_remove(struct absys_list* list, int idx) {
	int ii = 0;
	struct absys_list_node* node = list->head;
	while(ii + node->size < idx) {
		ii += node->size;
		node = node->next;
	}
	_absys_list_rem(list, node, idx - ii);
}

ABSYS_API void absys_list_push(struct absys_list* list, void* value) {
	_absys_list_add(list, list->tail, list->tail->size, value);
}

ABSYS_API void absys_list_pop(struct absys_list* list, void* elem) {
	void* value_store = list->tail->data + list->elem_size * (list->tail->size - 1);
	memcpy(elem, value_store, list->elem_size);
	_absys_list_rem(list, list->tail, list->tail->size - 1);
}

ABSYS_API void absys_list_it_init(struct absys_list_it* iter, struct absys_list* list) {
	iter->list = list;
	iter->node = list->head;
	iter->cursor = 0;
}

ABSYS_API void absys_list_it_exit(struct absys_list_it* iter) {

}

ABSYS_API void absys_list_it_get(struct absys_list_it* iter, void* value) {
	memcpy(value, iter->node->data + iter->cursor * iter->list->elem_size, iter->list->elem_size);
}

ABSYS_API bool absys_list_it_next(struct absys_list_it* iter) {
	if (iter->cursor < iter->node->size - 1) {
		++ iter->cursor;
		return true;
	}
	else if (iter->node->next != iter->list->head) {
		iter->node = iter->node->next;
		iter->cursor = 0;
		return true;
	}
	return false;
}
