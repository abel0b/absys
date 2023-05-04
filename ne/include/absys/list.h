#ifndef __ABSYS_LIST_h
#define __ABSYS_LIST_h

#include <stdbool.h>
#include "config.h"

struct absys_list_node {
	int size;
	void* data[ABSYS_LIST_UNROLL_FACTOR];
	struct absys_list_node * prev;
	struct absys_list_node * next;
};

struct absys_list {
    int size;
    struct absys_list_node* head;
    struct absys_list_node* tail;
    struct absys_objpool node_pool;
};


ABSYS_API void absys_list_new(struct absys_list* list, size_t elem_size);
ABSYS_API void absys_list_del(struct absys_list* list);
ABSYS_API bool absys_list_empty(struct absys_list* list);
ABSYS_API void* absys_list_get(struct absys_list* list, int idx);
ABSYS_API void* absys_list_head(struct absys_list* list);
ABSYS_API void* absys_list_tail(struct absys_list* list);
ABSYS_API void absys_list_insert(struct absys_list* list, int idx, void* elem);
ABSYS_API void absys_list_push(struct absys_list* list, void* elem);
ABSYS_API void absys_list_pop(struct absys_list* list, void* elem);


#define absys_list_t(name) struct absys_##name##_list 

#define absys_list_decl_aux(TYPE, NAME, QUAL) \
struct absys_##NAME##_list {\
    TYPE* data;\
    int size;\
    int capacity;\
};\
struct absys_##NAME##_list_it {\
    int cursor;\
    struct absys_##NAME##_list * list;\
};\
ABSYS_API void absys_##NAME##_list_new(struct absys_##NAME##_list* list);\
ABSYS_API void absys_##NAME##_list_del(struct absys_##NAME##_list* list);\
ABSYS_API bool absys_##NAME##_list_empty(struct absys_##NAME##_list* list);\
ABSYS_API int absys_##NAME##_list_size(struct absys_##NAME##_list* list);\
ABSYS_API void absys_##NAME##_list_reserve(struct absys_##NAME##_list* list, int newcap);\
ABSYS_API void absys_##NAME##_list_resize(struct absys_##NAME##_list* list, int newsize);\
ABSYS_API void absys_##NAME##_list_push(struct absys_##NAME##_list* list, QUAL TYPE elem);\
ABSYS_API TYPE absys_##NAME##_list_get(struct absys_##NAME##_list* list, int idx);\
ABSYS_API TYPE *absys_##NAME##_list_get_ref(struct absys_##NAME##_list* list, int idx);\
ABSYS_API TYPE absys_##NAME##_list_first(struct absys_##NAME##_list* list);\
ABSYS_API TYPE absys_##NAME##_list_last(struct absys_##NAME##_list* list);\
ABSYS_API TYPE * absys_##NAME##_list_last_ref(struct absys_##NAME##_list* list);\
ABSYS_API TYPE absys_##NAME##_list_pop(struct absys_##NAME##_list* list);\
ABSYS_API void absys_##NAME##_list_fill(struct absys_##NAME##_list* list, QUAL TYPE elem);\
ABSYS_API void absys_##NAME##_list_it_new(struct absys_##NAME##_list_it* iter, struct absys_##NAME##_list* list);\
ABSYS_API void absys_##NAME##_list_it_del(struct absys_##NAME##_list_it* iter);\
ABSYS_API void absys_##NAME##_list_it_get(struct absys_##NAME##_list_it* iter, TYPE* value);\
ABSYS_API bool absys_##NAME##_list_it_next(struct absys_##NAME##_list_it* iter);

#define absys_list_decl(TYPE, NAME) absys_list_decl_aux(TYPE,NAME,const)
#define absys_ptr_list_decl(TYPE, NAME) absys_list_decl_aux(TYPE,NAME,)

#endif
