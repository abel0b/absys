#ifndef __ABSYS_PLUGIN_H__
#define __ABSYS_PLUGIN_H__

#include "absys/vec.h"
#include "absys/hook.h"

struct absys_plugin {
	void* dll;
        char* name;
        void* state;
        int (*exec_init)(struct absys_plugin*, struct absys_hook_store*);
        void (*exec_destroy)(struct absys_plugin*);
};

absys_vec_decl(struct absys_plugin, plugin)

struct absys_plugin_store {
	struct absys_plugin_vec plugins;
	struct absys_hook_store* hooks;
};

void absys_plugin_store_new(struct absys_plugin_store* plugins);

void absys_plugin_store_del(struct absys_plugin_store* plugin);

struct absys_plugin* absys_plugin_register(struct absys_plugin_store* plugins, char* name, int (*plugin_init)(struct absys_plugin*, struct absys_hook_store*), void (*plugin_destroy)(struct absys_plugin*));

#endif
