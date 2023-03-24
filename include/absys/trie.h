#ifndef __ABSYS_TRIE__H
#define __ABSYS_TRIE__H

#include <stdlib.h>
#include <stdbool.h>
#include "absys/mem.h"
#include "absys/defs.h"
#include "absys/vec.h"
#include "absys/strstack.h"
#include "absys/objpool.h"

struct absys_trie_node {
	struct absys_ptr_vec children;
	char* prefix; 
	void* value;
	bool isset;
};

struct absys_trie {
    struct absys_str_stack strstack;
    struct absys_trie_node* root;
    struct absys_objpool node_pool;
    int size;
};

extern void* absys_trie_notfound;


ABSYS_API void absys_trie_new(struct absys_trie* trie);
ABSYS_API void absys_trie_del(struct absys_trie* trie);
ABSYS_API int absys_trie_size(struct absys_trie* trie);
ABSYS_API void absys_trie_set(struct absys_trie* trie, const char* key, void* value);
ABSYS_API void* absys_trie_get(struct absys_trie* trie, const char* key);
ABSYS_API void absys_trie_print(struct absys_trie* trie);

struct absys_trie_it {
	struct absys_ptr_vec node_stack;
	struct absys_ptr_vec str_stack;
	struct absys_objpool str_pool;
	struct absys_str* cur_key;
	void* cur_value;
};

ABSYS_API void absys_trie_it_new(struct absys_trie_it* iter, struct absys_trie* set);
ABSYS_API void absys_trie_it_del(struct absys_trie_it* iter);
ABSYS_API void absys_trie_it_get(struct absys_trie_it* iter, char**key, void**value);
ABSYS_API bool absys_trie_it_next(struct absys_trie_it* iter);
ABSYS_API bool absys_trie_it_next_prefix(struct absys_trie_it* iter, const char* prefix);
#endif
