#ifndef ABSYSVEC__H
#define ABSYSVEC__H

#include <stdlib.h>
#include <stdbool.h>
#include "absys/log.h"
#include "absys/mem.h"
#include "absys/defs.h"
#include "absys/utils.h"

// TODO: add safe mode

struct absys_vec {
    void* data;
    int size;
    int capacity;
    size_t elem_size;
};

ABSYS_API void absys_vec_new(struct absys_vec* vec, size_t elem_size);
ABSYS_API void absys_vec_del(struct absys_vec* vec);
ABSYS_API bool absys_vec_empty(struct absys_vec* vec);
ABSYS_API int absys_vec_size(struct absys_vec* vec);
ABSYS_API void* absys_vec_get(struct absys_vec* vec, int idx);
ABSYS_API void* absys_vec_last(struct absys_vec* vec);
ABSYS_API void absys_vec_reserve(struct absys_vec* vec, int newcap);
ABSYS_API void absys_vec_resize(struct absys_vec* vec, int newsize);
ABSYS_API void absys_vec_push(struct absys_vec* vec, void* elem);
ABSYS_API void absys_vec_pop(struct absys_vec* vec, void* elem);
ABSYS_API void absys_vec_peek(struct absys_vec* vec, void* elem);
ABSYS_API void absys_vec_fill(struct absys_vec* vec, void* elem);

#define absys_vec_decl_aux(TYPE, NAME, QUAL) \
struct absys_##NAME##_vec {\
    TYPE* data;\
    int size;\
    int capacity;\
};\
struct absys_##NAME##_vec_it {\
    int cursor;\
    struct absys_##NAME##_vec * vec;\
};\
ABSYS_API void absys_##NAME##_vec_new(struct absys_##NAME##_vec* vec);\
ABSYS_API void absys_##NAME##_vec_del(struct absys_##NAME##_vec* vec);\
ABSYS_API bool absys_##NAME##_vec_empty(struct absys_##NAME##_vec* vec);\
ABSYS_API int absys_##NAME##_vec_size(struct absys_##NAME##_vec* vec);\
ABSYS_API void absys_##NAME##_vec_reserve(struct absys_##NAME##_vec* vec, int newcap);\
ABSYS_API void absys_##NAME##_vec_resize(struct absys_##NAME##_vec* vec, int newsize);\
ABSYS_API void absys_##NAME##_vec_push(struct absys_##NAME##_vec* vec, QUAL TYPE elem);\
ABSYS_API void absys_##NAME##_vec_set(struct absys_##NAME##_vec* vec, int pos, QUAL TYPE elem);\
ABSYS_API TYPE absys_##NAME##_vec_get(struct absys_##NAME##_vec* vec, int idx);\
ABSYS_API TYPE *absys_##NAME##_vec_get_ref(struct absys_##NAME##_vec* vec, int idx);\
ABSYS_API TYPE absys_##NAME##_vec_first(struct absys_##NAME##_vec* vec);\
ABSYS_API TYPE absys_##NAME##_vec_last(struct absys_##NAME##_vec* vec);\
ABSYS_API TYPE * absys_##NAME##_vec_last_ref(struct absys_##NAME##_vec* vec);\
ABSYS_API TYPE absys_##NAME##_vec_pop(struct absys_##NAME##_vec* vec);\
ABSYS_API void absys_##NAME##_vec_fill(struct absys_##NAME##_vec* vec, QUAL TYPE elem);\
ABSYS_API void absys_##NAME##_vec_it_new(struct absys_##NAME##_vec_it* iter, struct absys_##NAME##_vec* vec);\
ABSYS_API void absys_##NAME##_vec_it_del(struct absys_##NAME##_vec_it* iter);\
ABSYS_API void absys_##NAME##_vec_it_get(struct absys_##NAME##_vec_it* iter, TYPE* value);\
ABSYS_API bool absys_##NAME##_vec_it_next(struct absys_##NAME##_vec_it* iter);


#define absys_vec_decl(TYPE, NAME) absys_vec_decl_aux(TYPE,NAME,const)
#define absys_ptr_vec_decl(TYPE, NAME) absys_vec_decl_aux(TYPE,NAME,)

#define absys_vec_impl_aux(TYPE, NAME, QUAL)\
ABSYS_API void absys_##NAME##_vec_new(struct absys_##NAME##_vec* vec) {\
    vec->capacity = 0;\
    vec->size = 0;\
    vec->data = NULL;\
}\
ABSYS_API void absys_##NAME##_vec_del(struct absys_##NAME##_vec* vec) {\
    if (vec->data) {\
        absys_free(vec->data);\
    }\
}\
ABSYS_API bool absys_##NAME##_vec_empty(struct absys_##NAME##_vec* vec) {\
    return !vec->size;\
}\
ABSYS_API int absys_##NAME##_vec_size(struct absys_##NAME##_vec* vec) {\
    return vec->size;\
}\
ABSYS_API void absys_##NAME##_vec_reserve(struct absys_##NAME##_vec* vec, int newcap) {\
    if (newcap > vec->capacity) {\
        vec->capacity = newcap;\
        vec->data = absys_realloc(vec->data, vec->capacity * sizeof(TYPE));\
    }\
}\
ABSYS_API void absys_##NAME##_vec_resize(struct absys_##NAME##_vec* vec, int newsize) {\
    absys_##NAME##_vec_reserve(vec, newsize);\
    vec->size = newsize;\
}\
ABSYS_API void absys_##NAME##_vec_push(struct absys_##NAME##_vec* vec, QUAL TYPE elem) {\
    if (vec->capacity == vec->size) {\
        absys_##NAME##_vec_reserve(vec, (vec->capacity == 0)? 8 : 2 * vec->capacity);\
    }\
    vec->data[vec->size] = elem;\
    ++ vec->size;\
}\
ABSYS_API void absys_##NAME##_vec_set(struct absys_##NAME##_vec* vec, int pos, QUAL TYPE elem) {\
    vec->data[pos] = elem;\
}\
ABSYS_API TYPE absys_##NAME##_vec_pop(struct absys_##NAME##_vec* vec) {\
    return vec->data[--vec->size];\
}\
ABSYS_API TYPE absys_##NAME##_vec_get(struct absys_##NAME##_vec* vec, int idx) {\
    return vec->data[idx];\
}\
ABSYS_API TYPE *absys_##NAME##_vec_get_ref(struct absys_##NAME##_vec* vec, int idx) {\
    return &vec->data[idx];\
}\
ABSYS_API TYPE absys_##NAME##_vec_first(struct absys_##NAME##_vec* vec) {\
    return vec->data[0];\
}\
ABSYS_API TYPE absys_##NAME##_vec_last(struct absys_##NAME##_vec* vec) {\
    return vec->data[vec->size - 1];\
}\
ABSYS_API TYPE * absys_##NAME##_vec_last_ref(struct absys_##NAME##_vec* vec) {\
    return &vec->data[vec->size - 1];\
}\
ABSYS_API void absys_##NAME##_vec_fill(struct absys_##NAME##_vec* vec, QUAL TYPE elem) {\
    for (int i = 0; i < vec->size; ++i) {\
        vec->data[i] = elem;\
    }\
}\
ABSYS_API void absys_##NAME##_vec_it_new(struct absys_##NAME##_vec_it* iter, struct absys_##NAME##_vec* vec) {\
	iter->vec = vec;\
	iter->cursor = -1;\
}\
ABSYS_API void absys_##NAME##_vec_it_del(struct absys_##NAME##_vec_it* iter) {\
absys_unused(iter);\
}\
ABSYS_API void absys_##NAME##_vec_it_get(struct absys_##NAME##_vec_it* iter, TYPE* value) {\
	*value = iter->vec->data[iter->cursor];\
}\
ABSYS_API bool absys_##NAME##_vec_it_next(struct absys_##NAME##_vec_it* iter) {\
	++ iter->cursor;\
	return iter->cursor < iter->vec->size;\
}

#define absys_vec_impl(TYPE, NAME) absys_vec_impl_aux(TYPE,NAME,const)
#define absys_ptr_vec_impl(TYPE, NAME) absys_vec_impl_aux(TYPE,NAME,)

absys_vec_decl(char, char)
absys_vec_decl(int, int)
absys_vec_decl(float, float)
absys_vec_decl(double, double)
absys_ptr_vec_decl(char*, cstr)
absys_ptr_vec_decl(void*, ptr)

#endif
