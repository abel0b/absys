#ifndef ABSYSDICT__H
#define ABSYSDICT__H

#include "absys/strstack.h"
#include "absys/defs.h"
#include <stdint.h>
#include <string.h>

extern int ABSYS_NUMBUCKETS;
extern int ABSYS_INITBUCKETCAPACITY;

struct absys_dictentry {
    char* key;
    void* value;
};

struct absys_dict {
    struct absys_str_stack key_pool;
    int numbuckets;
    struct absys_dictentry** buckets;
    int* sizes;
    int* capacities;
};

extern void* absys_dict_notfound;

ABSYS_API void absys_dict_init(struct absys_dict* dict);
ABSYS_API void absys_dict_exit(struct absys_dict* dict);
ABSYS_API unsigned long absys_dict_hash(const char *str);
ABSYS_API void absys_dict_set(struct absys_dict* dict, const char* key, void* value);
ABSYS_API void* absys_dict_get(struct absys_dict* dict, const char* key);
ABSYS_API bool absys_dict_has(struct absys_dict* dict, const char* key);
ABSYS_API void absys_dict_display(struct absys_dict* dict);

#define absys_dict_decl(TYPE, NAME) \
struct absys_##NAME##_dictentry {\
    char* key;\
    TYPE value;\
};\
struct absys_##NAME##_dict {\
    struct absys_str_stack key_pool;\
    int numbuckets;\
    struct absys_##NAME##_dictentry** buckets;\
    int* sizes;\
    int* capacities;\
};\
ABSYS_API void absys_##NAME##_dict_init(struct absys_##NAME##_dict* dict);\
ABSYS_API void absys_##NAME##_dict_exit(struct absys_##NAME##_dict* dict);\
ABSYS_API void absys_##NAME##_dict_set(struct absys_##NAME##_dict* dict, const char* key, TYPE value);\
ABSYS_API TYPE absys_##NAME##_dict_get(struct absys_##NAME##_dict* dict, const char* key);\
ABSYS_API TYPE * absys_##NAME##_dict_get_ref(struct absys_##NAME##_dict* dict, const char* key);\
ABSYS_API bool absys_##NAME##_dict_has(struct absys_##NAME##_dict* dict, const char* key);


#define absys_dict_impl(TYPE, NAME) \
ABSYS_API void absys_##NAME##_dict_init(struct absys_##NAME##_dict* dict) {\
    dict->numbuckets = ABSYS_NUMBUCKETS;\
    dict->sizes = absys_malloc(sizeof(dict->sizes[0]) * dict->numbuckets);\
    memset(dict->sizes, 0, sizeof(dict->sizes[0]) * dict->numbuckets);\
    dict->capacities = absys_malloc(sizeof(dict->capacities[0]) * dict->numbuckets);\
    memset(dict->capacities, 0, sizeof(dict->capacities[0]) * dict->numbuckets);\
    dict->buckets = NULL;\
    absys_str_stack_init(&dict->key_pool);\
}\
ABSYS_API void absys_##NAME##_dict_set(struct absys_##NAME##_dict* dict, const char* key, TYPE value) {\
    unsigned long bucketid = absys_dict_hash(key) % dict->numbuckets;\
    if (!dict->buckets) {\
        dict->buckets = absys_malloc(sizeof(dict->buckets[0]) * dict->numbuckets);\
    }\
    if (!dict->capacities[bucketid]) {\
        dict->capacities[bucketid] = ABSYS_INITBUCKETCAPACITY;\
        dict->buckets[bucketid] = absys_malloc(sizeof(dict->buckets[0][0]) * dict->capacities[bucketid]);\
    }\
    else if (dict->capacities[bucketid] == dict->sizes[bucketid]) {\
        dict->capacities[bucketid] *= 2;\
        dict->buckets[bucketid] = absys_realloc(dict->buckets[bucketid], sizeof(dict->buckets[0][0]) * dict->capacities[bucketid]);\
    }\
    for(int i = 0; i < dict->sizes[bucketid]; ++i) {\
        if(strcmp(dict->buckets[bucketid][i].key, key) == 0) {\
    	    dict->buckets[bucketid][i].value = value;\
	    return;\
	}\
    }\
    \
    dict->buckets[bucketid][dict->sizes[bucketid]].key = absys_str_stack_push(&dict->key_pool, key);\
    dict->buckets[bucketid][dict->sizes[bucketid]].value = value;\
    ++ dict->sizes[bucketid];\
}\
ABSYS_API TYPE absys_##NAME##_dict_get(struct absys_##NAME##_dict* dict, const char* key) {\
    unsigned long bucketid = absys_dict_hash(key) % dict->numbuckets;\
    for(int i = 0; i < dict->sizes[bucketid]; ++ i) {\
        if (strcmp(key, dict->buckets[bucketid][i].key) == 0) {\
            return dict->buckets[bucketid][i].value;\
        }\
    }\
    exit(1);\
}\
ABSYS_API TYPE * absys_##NAME##_dict_get_ref(struct absys_##NAME##_dict* dict, const char* key) {\
    unsigned long bucketid = absys_dict_hash(key) % dict->numbuckets;\
    for(int i = 0; i < dict->sizes[bucketid]; ++ i) {\
        if (strcmp(key, dict->buckets[bucketid][i].key) == 0) {\
            return &dict->buckets[bucketid][i].value;\
        }\
    }\
    exit(1);\
}\
ABSYS_API bool absys_##NAME##_dict_has(struct absys_##NAME##_dict* dict, const char* key) {\
    unsigned long bucketid = absys_dict_hash(key) % dict->numbuckets;\
    for(int i = 0; i < dict->sizes[bucketid]; ++ i) {\
        if (strcmp(key, dict->buckets[bucketid][i].key) == 0) {\
            return true;\
        }\
    }\
    return false;\
}\
ABSYS_API void absys_##NAME##_dict_exit(struct absys_##NAME##_dict* dict) {\
    for(int i = 0; i < dict->numbuckets; ++ i) {\
        if (dict->capacities[i]) {\
            absys_free(dict->buckets[i]);\
        }\
    }\
    absys_str_stack_exit(&dict->key_pool);\
    absys_free(dict->buckets);\
    absys_free(dict->sizes);\
    absys_free(dict->capacities);\
}

#endif
