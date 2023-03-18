#include "absys/set.h"
#include "absys/str.h"

ABSYS_API void absys_cstr_set_new(struct absys_cstr_set* set) {
	absys_trie_new(&set->trie);
	set->size = 0;
}

ABSYS_API bool absys_cstr_set_empty(struct absys_cstr_set* set) {
	return !set->size;
}

ABSYS_API void absys_cstr_set_del(struct absys_cstr_set* set) {
	absys_trie_del(&set->trie);
}

ABSYS_API void absys_cstr_set_add(struct absys_cstr_set* set, char* cstr) {
	absys_trie_set(&set->trie, cstr, (void*)0x42);
	set->size = set->trie.size;
}

ABSYS_API void absys_cstr_set_it_new(struct absys_cstr_set_it* iter, struct absys_cstr_set* set) {
	absys_ptr_vec_new(&iter->node_stack);
	absys_ptr_vec_new(&iter->str_stack);
	absys_ptr_vec_push(&iter->node_stack, (void*) &((struct absys_trie_node*)set->trie.nodes.data)[0]);
	absys_objpool_new(&iter->str_pool, sizeof(struct absys_str), NULL);
	iter->cur = NULL;
}

ABSYS_API void absys_cstr_set_it_del(struct absys_cstr_set_it* iter) {
	absys_ptr_vec_del(&iter->node_stack);
	absys_ptr_vec_del(&iter->str_stack);
	absys_objpool_del(&iter->str_pool);
	if (iter->cur) {
		absys_str_del(iter->cur);
	}
}

ABSYS_API char* absys_cstr_set_it_get(struct absys_cstr_set_it* iter) {
	return iter->cur->data;
}

ABSYS_API bool absys_cstr_set_it_next(struct absys_cstr_set_it* iter) {
	if (absys_ptr_vec_empty(&iter->node_stack)) {
		return false;
	}

	struct absys_trie_node* node = (struct absys_trie_node*) absys_ptr_vec_pop(&iter->node_stack);
	struct absys_str* str = (struct absys_str*) absys_ptr_vec_pop(&iter->str_stack);

	for (int i = 0; i< node->children.size; ++i) {
		struct absys_trie_node* child = (struct absys_trie_node*) absys_ptr_vec_get(&node->children, i);
		struct absys_str* child_str = (struct absys_str*) absys_objpool_alloc(&iter->str_pool);
		absys_str_new(child_str);
		absys_str_cat(child_str, str->data);
		absys_str_cat(child_str, child->prefix);
		absys_ptr_vec_push(&iter->node_stack, (void*)child);
		absys_ptr_vec_push(&iter->str_stack, (void*)child_str);
	}

	if (iter->cur) {
		absys_str_del(iter->cur);
	}
	
	if (node->isset) {
		iter->cur = str;
		return true;
	}
	else {
		return absys_cstr_set_it_next(iter);
	}
	
}
