#include "absys/trie.h"
#include "absys/str.h"
#include <string.h>

void* absys_trie_notfound = (void*)"absys_trie_notfound";

void absys_trie_node_del(void* elem_ptr) {
        struct absys_trie_node* node = (struct absys_trie_node*)elem_ptr;
		absys_ptr_vec_del(&node->children);
}

ABSYS_API void absys_trie_new(struct absys_trie* trie) {
	absys_str_stack_new(&trie->strstack);
    absys_objpool_new(&trie->node_pool, sizeof(struct absys_trie_node), absys_trie_node_del);
	trie->size = 0;
    trie->root = (struct absys_trie_node*)absys_objpool_alloc(&trie->node_pool);
	absys_ptr_vec_new(&trie->root->children);
	trie->root->prefix = "";
	trie->root->value = NULL;
	trie->root->isset = false;
}

ABSYS_API void absys_trie_del(struct absys_trie* trie) {
	absys_str_stack_del(&trie->strstack);
    absys_objpool_del(&trie->node_pool);
}

// returns 0 if $str = $prefix
// prefix length if $prefix is a prefix of $str
// else a negative number 
static int absys_str_prefix_cmp(const char* prefix, const char* str) {
	int cnt = 0;
	while((*prefix != '\0') && (*str != '\0') && (*prefix == *str)) {
		cnt ++;
		prefix += sizeof(char);
		str += sizeof(char);
	}
	if ((*prefix == '\0') && (*str == '\0')) {
		return 0;
	}
	if ((*prefix == '\0') && (*str != '\0')) {
		return cnt;
	}
	return -1;
}

ABSYS_API void absys_trie_set(struct absys_trie* trie, const char* key, void* value) {
	struct absys_trie_node * node = trie->root;
	int keylen = strlen(key);

	if (*key == '\0') {
		trie->size += 1 - node->isset;
		node->isset = true;
		node->value = value;
		return;
	}

	int idx = 0;
	while (idx < keylen) {
		struct absys_trie_node* best_match = NULL;
		int best_match_cnt = 0;
		for (int i = 0; i < absys_ptr_vec_size(&node->children); ++i) {
			struct absys_trie_node* child = (struct absys_trie_node*)absys_ptr_vec_get(&node->children, i);
			int pos = absys_str_prefix_cmp(child->prefix, &key[idx]);
			if (pos > best_match_cnt) {
				best_match_cnt = pos;
				best_match = child;
				break;
			}
			else if (pos == 0 && (*child->prefix)) {
				// exact match
				trie->size += 1 - child->isset;
				child->isset = true;
				child->value = value;
				return; 
			}
		}
	
		if (best_match) {
			// split insert	
			int len_best_match = strlen(best_match->prefix);
			if (best_match_cnt < len_best_match) {
				char* newpref = absys_str_stack_push(&trie->strstack, &best_match->prefix[best_match_cnt]);
				struct absys_trie_node* newnode = (struct absys_trie_node*)absys_objpool_alloc(&trie->node_pool);
				newnode->children = best_match->children;
                newnode->prefix = newpref;
	            newnode->value = best_match->value;
	            newnode->isset = best_match->isset;

				absys_ptr_vec_new(&best_match->children);
				absys_ptr_vec_push(&best_match->children, (void*)newnode);
				best_match->prefix[best_match_cnt] = '\0';
				best_match->isset = false;
			}
			node = best_match;
			idx += best_match_cnt;
			continue;
		}

		// insert child
		struct absys_trie_node* newnode = (struct absys_trie_node*) absys_objpool_alloc(&trie->node_pool);
		absys_ptr_vec_new(&newnode->children);
		char* newpref = absys_str_stack_push(&trie->strstack, &key[idx]);
		newnode->prefix = newpref;
		newnode->value = value;
		newnode->isset = true;
		absys_ptr_vec_push(&node->children, (void*)newnode);
		++ trie->size;
		return;
	}
}

ABSYS_API int absys_trie_size(struct absys_trie* trie) {
	return trie->size;
}

static void absys_trie_print_rec(struct absys_trie_node* node, int indent_level) {
	for(int ii = 0; ii < indent_level; ++ii) {
		printf("\t");
	}

	if (node->isset) {
		printf("Node(\"%s\", %p)\n", node->prefix, node->value);
	}
	else {
		printf("Node(\"%s\", nullptr)\n", node->prefix);
	}

	for (int i = 0; i < absys_ptr_vec_size(&node->children); ++i) {
	    struct absys_trie_node* child = absys_ptr_vec_get(&node->children, i);
		absys_trie_print_rec(child, indent_level + 1);
	}
}

ABSYS_API void absys_trie_print(struct absys_trie* trie) {
	absys_trie_print_rec(trie->root, 0);
}

ABSYS_API void* absys_trie_get(struct absys_trie* trie, const char* key) {
	struct absys_trie_node * node = trie->root;
	int keylen = strlen(key);

	if (*key == '\0') {
		if (node->isset) {
			return node->value;
		}
		return absys_trie_notfound;
	}

	int idx = 0;
	while (idx < keylen) {
		struct absys_trie_node* best_match = NULL;
		int best_match_cnt = 0;
		for (int i = 0; i < node->children.size; ++i) {
			struct absys_trie_node* child = (struct absys_trie_node*) absys_ptr_vec_get(&node->children, i);
			int pos = absys_str_prefix_cmp(child->prefix, &key[idx]);
			if (pos > 0) {
				best_match_cnt = pos;
				best_match = child;
				break;
			}
			else if (pos == 0) {
				if (child->isset) {
					return child->value;
				}
				return absys_trie_notfound;
			}
		}

		if (best_match)	{
			node = best_match;
			idx += best_match_cnt;
			continue;
		}
		else {
			break;
		}
	}

	return absys_trie_notfound;
}

ABSYS_API void absys_trie_it_new(struct absys_trie_it* iter, struct absys_trie* trie) {
	absys_ptr_vec_new(&iter->node_stack);
	absys_ptr_vec_new(&iter->str_stack);
	absys_objpool_new(&iter->str_pool, sizeof(struct absys_str), NULL);
	iter->cur_key = NULL;
	iter->cur_value = NULL;

	struct absys_str* empty_str = (struct absys_str*) absys_objpool_alloc(&iter->str_pool);
	absys_str_new(empty_str);
	absys_ptr_vec_push(&iter->str_stack, (void*)empty_str);
	absys_ptr_vec_push(&iter->node_stack, (void*)trie->root);
}

ABSYS_API void absys_trie_it_del(struct absys_trie_it* iter) {
	absys_ptr_vec_del(&iter->node_stack);
	absys_ptr_vec_del(&iter->str_stack);
	absys_objpool_del(&iter->str_pool);
	if (iter->cur_key) {
		//absys_str_del(iter->cur_key);
	}
}

ABSYS_API void absys_trie_it_get(struct absys_trie_it* iter, char**key, void**value) {
	*key = iter->cur_key->data;
	*value = iter->cur_value;
}

ABSYS_API bool absys_trie_it_next_prefix(struct absys_trie_it* iter, const char* prefix) {
	if (absys_ptr_vec_empty(&iter->node_stack)) {
		return false;
	}

	if (prefix[0] == '\0') {
		return absys_trie_it_next(iter);
	}

	struct absys_trie_node* node = (struct absys_trie_node*) absys_ptr_vec_pop(&iter->node_stack);
	struct absys_str* str = (struct absys_str*) absys_ptr_vec_pop(&iter->str_stack);
	int keylen = strlen(prefix);

	int idx = 0;
	while (idx < keylen) {
		struct absys_trie_node* best_match = NULL;
		int best_match_cnt = 0;
		for (int i = 0; i < node->children.size; ++i) {
			struct absys_trie_node* child = (struct absys_trie_node*) absys_ptr_vec_get(&node->children, i);
			struct absys_str* child_str = (struct absys_str*) absys_objpool_alloc(&iter->str_pool);
			absys_str_new(child_str);
			absys_str_cat(child_str, str->data);
			absys_str_cat(child_str, child->prefix);


			int pos = absys_str_prefix_cmp(child->prefix, &prefix[idx]);
			if (pos > 0) {
				best_match_cnt = pos;
				best_match = child;
			}
			else if (pos == 0) {
				if (child->isset) {
					if (iter->cur_key) {
						absys_str_del(iter->cur_key);
					}
					iter->cur_key = child_str;
					iter->cur_value = child->value;
	
					for (int j = 0; j < absys_ptr_vec_size(&child->children); ++j) {
						struct absys_trie_node* child2 = (struct absys_trie_node*) absys_ptr_vec_get(&child->children, j);
						struct absys_str* child_str2 = (struct absys_str*) absys_objpool_alloc(&iter->str_pool);

						absys_str_new(child_str2);
						absys_str_cat(child_str2, str->data);
						absys_str_cat(child_str2, child->prefix);
						absys_str_cat(child_str2, child2->prefix);

						absys_ptr_vec_push(&iter->node_stack, (void*)child2);
						absys_ptr_vec_push(&iter->str_stack, (void*)child_str2);
					}
					return true;
				}
				else {
					for (int j = 0; j < absys_ptr_vec_size(&child->children); ++j) {
						struct absys_trie_node* child2 = (struct absys_trie_node*) absys_ptr_vec_get(&child->children, j);
						struct absys_str* child_str2 = (struct absys_str*) absys_objpool_alloc(&iter->str_pool);

						absys_str_new(child_str2);
						absys_str_cat(child_str2, str->data);
						absys_str_cat(child_str2, child->prefix);
						absys_str_cat(child_str2, child2->prefix);

						absys_ptr_vec_push(&iter->node_stack, (void*)child2);
						absys_ptr_vec_push(&iter->str_stack, (void*)child_str2);
					}
					absys_str_del(child_str);			
					return absys_trie_it_next(iter);
				}
			}
			else {

				int pos = absys_str_prefix_cmp(child->prefix, &prefix[idx]);
	
			}
			absys_str_del(child_str);
		}

		if (best_match)	{
			node = best_match;
			idx += best_match_cnt;
		}
		else {
			return false;
		}
	}
	exit(1);
	// unreachable
	return false;
}

ABSYS_API bool absys_trie_it_next(struct absys_trie_it* iter) {
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

	if (node->isset) {
		if (iter->cur_key) {
			absys_str_del(iter->cur_key);
		}
		iter->cur_key = str;
		iter->cur_value = node->value;
		return true;
	}
	else {
		//absys_str_del(str);
		return absys_trie_it_next(iter);
	}
	
}
