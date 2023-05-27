#ifndef __ABSYS_SET_H
#define __ABSYS_SET_H

#include "absys/trie.h"
#include "absys/vec.h"
#include "absys/strstack.h"
#include "absys/objpool.h"
#include <stdbool.h>

struct absys_cstr_set {
    struct absys_trie trie;
    int size;
};

ABSYS_API void absys_cstr_set_init(struct absys_cstr_set* set);
ABSYS_API void absys_cstr_set_exit(struct absys_cstr_set* set);
ABSYS_API bool absys_cstr_set_empty(struct absys_cstr_set* set);
ABSYS_API void absys_cstr_set_add(struct absys_cstr_set* set, char* cstr);

struct absys_cstr_set_it {
	struct absys_ptr_vec node_stack;
	struct absys_ptr_vec str_stack;
	struct absys_objpool str_pool;
	struct absys_str* cur;
};

ABSYS_API void absys_cstr_set_it_init(struct absys_cstr_set_it* iter, struct absys_cstr_set* set);

ABSYS_API void absys_cstr_set_it_exit(struct absys_cstr_set_it* iter);

ABSYS_API char* absys_cstr_set_it_get(struct absys_cstr_set_it* iter);

ABSYS_API bool absys_cstr_set_it_next(struct absys_cstr_set_it* iter);

#endif
