#ifndef ABLDICT__H
#define ABLDICT__H

#include "abl/strstack.h"
#include <stdint.h>

struct abl_dictentry {
    char* key;
    void* value;
};

struct abl_dict {
    struct abl_str_stack key_pool;
    int numbuckets;
    struct abl_dictentry** buckets;
    int* sizes;
    int* capacities;
};

void abl_dict_new(struct abl_dict* dict);
void abl_dict_set(struct abl_dict* dict, char* key, void* value);
void* abl_dict_get(struct abl_dict* dict, char* key);
void abl_dict_display(struct abl_dict* dict);
void abl_dict_del(struct abl_dict* dict);

#endif
