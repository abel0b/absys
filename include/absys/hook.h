#ifndef __ABSYS_HOOK_h
#define __ABSYS_HOOK_h

#include "absys/vec.h"
#include "absys/trie.h"
#include "absys/objpool.h"

#include <stdarg.h>

struct absys_hook;
typedef void (*absys_hook_cb)(struct absys_hook* hook, const char * chan, va_list args);

struct absys_hook {
        int chan;
        absys_hook_cb exec;
        void* state;
};

absys_vec_decl(struct absys_hook, hook)

struct absys_hook_store {
	struct absys_objpool hook_vec_pool;
	struct absys_trie hook_trie;
};

void absys_hook_store_init(struct absys_hook_store* hooks);

void absys_hook_store_exit(struct absys_hook_store* hooks);

struct absys_hook* absys_hook_subscribe(struct absys_hook_store* hooks, const char* chan, absys_hook_cb callback);

void absys_hook_publish(struct absys_hook_store* hooks, const char* chan, ...);

#endif
