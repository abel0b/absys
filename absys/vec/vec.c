#include "absys/vec.h"
#include "absys/mem.h"
#include <string.h>
#include "absys/utils.h"

// TODO: shrink vec allocated memory when removing elements

ABSYS_API void absys_vec_init(struct absys_vec* vec, size_t elem_size) {
    vec->capacity = 0;
    vec->size = 0;
    vec->data = NULL;
    vec->elem_size = elem_size;
}

ABSYS_API void absys_vec_exit(struct absys_vec* vec) {
    if (vec->data) {
        absys_free(vec->data);
    }
}

ABSYS_API bool absys_vec_empty(struct absys_vec* vec) {\
    return !vec->size;
}

ABSYS_API int absys_vec_size(struct absys_vec* vec) {\
    return vec->size;
}

ABSYS_API void absys_vec_reserve(struct absys_vec* vec, int newcap) {
    if (newcap > vec->capacity) {
        vec->capacity = newcap;
        vec->data = absys_realloc((char*)vec->data, vec->capacity * vec->elem_size);
    }
}

ABSYS_API void absys_vec_resize(struct absys_vec* vec, int newsize) {
    absys_vec_reserve(vec, newsize);
    vec->size = newsize;
}

ABSYS_API void absys_vec_push(struct absys_vec* vec, void* elem) {
    if (vec->capacity == vec->size) {
        absys_vec_reserve(vec, (vec->capacity == 0)? 8 : 2 * vec->capacity);
    }
    memcpy((char*)vec->data + vec->size * vec->elem_size , elem, vec->elem_size);
    ++ vec->size;
}

ABSYS_API void absys_vec_pop(struct absys_vec* vec, void* elem) {
#if DEBUG
    absys_assert(vec->size);
#endif
    if (elem != NULL) {
        memcpy(elem, (char*)vec->data + (vec->size - 1) * vec->elem_size, vec->elem_size);
    }
    -- vec->size;
}

ABSYS_API void absys_vec_peek(struct absys_vec* vec, void* elem) {
#if DEBUG
    absys_assert(vec->size);
#endif
    if (elem != NULL) {
        memcpy(elem, (char*)vec->data + (vec->size - 1) * vec->elem_size, vec->elem_size);
    }
}

ABSYS_API void* absys_vec_get(struct absys_vec* vec, int idx) {
#if DEBUG
    absys_assert(idx < vec->size);
#endif
    return (char*)vec->data + idx * vec->elem_size;
}

ABSYS_API void* absys_vec_last(struct absys_vec* vec) {
    void* last = (char*)vec->data + (vec->size - 1) * vec->elem_size;
    return last;
}

ABSYS_API void absys_vec_fill(struct absys_vec* vec, void* elem) {
    for (int i = 0; i < vec->size; ++i) {
        memcpy((char*)vec->data + i * vec->elem_size, elem, vec->elem_size);
    }
}

absys_vec_impl(char, char)
absys_vec_impl(int, int)
absys_ptr_vec_impl(char*, cstr)
absys_ptr_vec_impl(void*, ptr)
absys_vec_impl(float, float)
absys_vec_impl(double, double)
