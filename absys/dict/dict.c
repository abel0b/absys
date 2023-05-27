#include "absys/dict.h"
#include "absys/mem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ABSYS_NUMBUCKETS = 8;
int ABSYS_INITBUCKETCAPACITY = 8;
void* absys_dict_notfound = (void*)"absys_dict_notfound";

ABSYS_API unsigned long absys_dict_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

ABSYS_API void absys_dict_init(struct absys_dict* dict) {
    dict->numbuckets = ABSYS_NUMBUCKETS;
    dict->sizes = absys_malloc(sizeof(dict->sizes[0]) * dict->numbuckets);
    memset(dict->sizes, 0, sizeof(dict->sizes[0]) * dict->numbuckets);
    dict->capacities = absys_malloc(sizeof(dict->capacities[0]) * dict->numbuckets);
    memset(dict->capacities, 0, sizeof(dict->capacities[0]) * dict->numbuckets);
    dict->buckets = NULL;
    absys_str_stack_init(&dict->key_pool);
}

ABSYS_API void absys_dict_set(struct absys_dict* dict, const char* key, void* value) {
    unsigned long bucketid = absys_dict_hash(key) % dict->numbuckets;
    if (!dict->buckets) {
        dict->buckets = absys_malloc(sizeof(dict->buckets[0]) * dict->numbuckets);
    }
    if (!dict->capacities[bucketid]) {
        dict->capacities[bucketid] = ABSYS_INITBUCKETCAPACITY;
        dict->buckets[bucketid] = absys_malloc(sizeof(dict->buckets[0][0]) * dict->capacities[bucketid]);
    }
    else if (dict->capacities[bucketid] == dict->sizes[bucketid]) {
        dict->capacities[bucketid] *= 2;
        dict->buckets[bucketid] = absys_realloc(dict->buckets[bucketid], sizeof(dict->buckets[0][0]) * dict->capacities[bucketid]);
    }

    for(int i = 0; i < dict->sizes[bucketid]; ++i) {
        if(strcmp(dict->buckets[bucketid][i].key, key) == 0) { 
    	    dict->buckets[bucketid][i].value = value;
	    return;
	}
    }
    
    dict->buckets[bucketid][dict->sizes[bucketid]].key = absys_str_stack_push(&dict->key_pool, key);
    dict->buckets[bucketid][dict->sizes[bucketid]].value = value;
    ++ dict->sizes[bucketid];
}

ABSYS_API void* absys_dict_get(struct absys_dict* dict, const char* key) {
    unsigned long bucketid = absys_dict_hash(key) % dict->numbuckets;
    for(int i = 0; i < dict->sizes[bucketid]; ++ i) {
        if (strcmp(key, dict->buckets[bucketid][i].key) == 0) {
            return dict->buckets[bucketid][i].value;
        }
    }
    return absys_dict_notfound;
}

ABSYS_API bool absys_dict_has(struct absys_dict* dict, const char* key) {
    return absys_dict_get(dict, key) != absys_dict_notfound;
}

ABSYS_API void absys_dict_exit(struct absys_dict* dict) {
    for(int i = 0; i < dict->numbuckets; ++ i) {
        if (dict->capacities[i]) {
            absys_free(dict->buckets[i]);
        }
    }
    absys_str_stack_exit(&dict->key_pool);
    absys_free(dict->buckets);
    absys_free(dict->sizes);
    absys_free(dict->capacities);
}

ABSYS_API void absys_dict_display(struct absys_dict* dict) {
    for(int i = 0; i < dict->numbuckets; ++ i) {
        if (dict->sizes[i]) {
            for(int j = 0; j < dict->sizes[i]; ++ j) {
                printf("%s => %p\n", dict->buckets[i][j].key, dict->buckets[i][j].value);
            }
        }
    }
}
