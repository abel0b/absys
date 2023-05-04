#include "absys/list.h"

ABSYS_API void absys_list_new(struct absys_list* list, size_t elem_size) {
	list->head = NULL;
	list->size = 0;
	list->elem_size = elem_size;
	absys_objpool_new(&list->node_pool, sizeof(struct absys_list_node), NULL);
}

ABSYS_API void absys_list_del(struct absys_list* list) {
	absys_objpool_del(&list->node_pool);
}

ABSYS_API bool absys_list_empty(struct absys_list* list) {
	return list->head == list->head->next;
}

ABSYS_API void* absys_list_get(struct absys_list* list, int idx) {
	int ii = 0;
	struct absys_list_node* node = list->head;
	while(ii + node->size < idx) {
		// TODO: if (node == NULL) out_of_bound
		ii += node->size;
		node = node->next;
	}
	return &node->data[idx - ii];
}

ABSYS_API void* absys_list_head(struct absys_list* list) {
	return list->head->data;
}

ABSYS_API void* absys_list_tail(struct absys_list* list) {
	return list->tail->data;
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
	memmove(value_store + list->elem_size, value_store, list->elem_size * (node->size - offset));
	memcpy(value_store, value, list->elem_size);
	++ node->size;
}

void _absys_list_rem(struct absys_list* list, struct absys_list_node* node, int offset) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	// TODO: objpool dealloc
	void* value_store = node->data + list->elem_size * offset;
	memmove(value_store, value_store + list->elem_size, list->elem_size * (node->size - offset));
	-- node->size;
}

ABSYS_API void absys_list_insert(struct absys_list* list, int idx, void* elem) {
	int ii = 0;
	struct absys_list_node* node = list->head;
	while(ii + node->size < idx) {
		ii += node->size;
		node = node->next;
	}
	_absys_list_add(list, node, idx - ii, elem);
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

ABSYS_API void absys_list_push(struct absys_list* list, void* elem) {
	_absys_list_add(list, list->tail, list->tail->size, elem);
}

ABSYS_API void absys_list_pop(struct absys_list* list, void* elem) {

}
