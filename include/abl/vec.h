#ifndef ABLVEC__H
#define ABLVEC__H

#include <stdlib.h>
#include <assert.h>
#include "abl/log.h"
#include "abl/mem.h"

// TODO: add safe mode

struct abl_vec {
    void* data;
    int size;
    int capacity;
    size_t elem_size;
};

void abl_vec_new(struct abl_vec* vec, size_t elem_size);
void abl_vec_del(struct abl_vec* vec);
void* abl_vec_get(struct abl_vec* vec, int idx);
void* abl_vec_last(struct abl_vec* vec);
void abl_vec_reserve(struct abl_vec* vec, int newcap);
void abl_vec_resize(struct abl_vec* vec, int newsize);
void abl_vec_push(struct abl_vec* vec, void* elem);
void abl_vec_pop(struct abl_vec* vec, void* elem);
void abl_vec_peek(struct abl_vec* vec, void* elem);
void abl_vec_fill(struct abl_vec* vec, void* elem);

#define abl_vec_decl(TYPE, NAME) \
struct abl_vec_##NAME {\
    TYPE* data;\
    int size;\
    int capacity;\
};\
void abl_vec_##NAME##_new(struct abl_vec_##NAME* vec);\
void abl_vec_##NAME##_del(struct abl_vec_##NAME* vec);\
void abl_vec_##NAME##_reserve(struct abl_vec_##NAME* vec, int newcap);\
void abl_vec_##NAME##_resize(struct abl_vec_##NAME* vec, int newsize);\
void abl_vec_##NAME##_push(struct abl_vec_##NAME* vec, TYPE elem);\
TYPE abl_vec_##NAME##_get(struct abl_vec_##NAME* vec, int idx);\
TYPE abl_vec_##NAME##_first(struct abl_vec_##NAME* vec);\
TYPE abl_vec_##NAME##_last(struct abl_vec_##NAME* vec);\
TYPE abl_vec_##NAME##_pop(struct abl_vec_##NAME* vec);\
void abl_vec_##NAME##_fill(struct abl_vec_##NAME* vec, TYPE elem);

#define abl_vec_impl(TYPE, NAME)\
void abl_vec_##NAME##_new(struct abl_vec_##NAME* vec) {\
    vec->capacity = 0;\
    vec->size = 0;\
    vec->data = NULL;\
}\
void abl_vec_##NAME##_del(struct abl_vec_##NAME* vec) {\
    if (vec->data) {\
        abl_free(vec->data);\
    }\
}\
void abl_vec_##NAME##_reserve(struct abl_vec_##NAME* vec, int newcap) {\
    if (newcap > vec->capacity) {\
        vec->capacity = newcap;\
        vec->data = abl_realloc(vec->data, vec->capacity * sizeof(TYPE));\
    }\
}\
void abl_vec_##NAME##_resize(struct abl_vec_##NAME* vec, int newsize) {\
    abl_vec_##NAME##_reserve(vec, newsize);\
    vec->size = newsize;\
}\
void abl_vec_##NAME##_push(struct abl_vec_##NAME* vec, TYPE elem) {\
    if (vec->capacity == vec->size) {\
        abl_vec_##NAME##_reserve(vec, (vec->capacity == 0)? 8 : 2 * vec->capacity);\
    }\
   vec->data[vec->size] = elem;\
    ++ vec->size;\
}\
TYPE abl_vec_##NAME##_pop(struct abl_vec_##NAME* vec) {\
    assert(vec->size > 0);\
    -- vec->size;\
    return vec->data[vec->size];\
}\
TYPE abl_vec_##NAME##_get(struct abl_vec_##NAME* vec, int idx) {\
    return vec->data[idx];\
}\
TYPE abl_vec_##NAME##_last(struct abl_vec_##NAME* vec) {\
    return vec->data[vec->size - 1];\
}\
void abl_vec_##NAME##_fill(struct abl_vec_##NAME* vec, TYPE elem) {\
    for (int i = 0; i < vec->size; ++i) {\
        vec->data[i] = elem;\
    }\
}

abl_vec_decl(char, char)
abl_vec_decl(int, int)
abl_vec_decl(char*, cstr)


#endif
