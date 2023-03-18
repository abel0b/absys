#include "absys/strstack.h"
#include "absys/log.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

ABSYS_API void absys_str_stack_new(struct absys_str_stack* str_stack) {
    absys_objpool_new(&str_stack->objpool, sizeof(char), NULL);
    absys_cstr_vec_new(&str_stack->stack);
}

ABSYS_API char* absys_str_stack_pushf(struct absys_str_stack* str_stack, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    char* dest = absys_objpool_arralloc(&str_stack->objpool, len + 1);
    va_start(args, fmt);
    vsnprintf(dest, len + 1, fmt, args);
    va_end(args);

    absys_cstr_vec_push(&str_stack->stack, dest);
#if DEBUG
    // absys_ilog("str_stack push %s", dest);
#endif
    return dest;
}

ABSYS_API char* absys_str_stack_push(struct absys_str_stack* str_stack, const char* str) {
    int len = strlen(str);

    char* dest = absys_objpool_arralloc(&str_stack->objpool, len + 1);
    strcpy(dest, str);
    absys_cstr_vec_push(&str_stack->stack, dest);
#if DEBUG
    // absys_ilog("str_stack push %s", dest);
#endif
    return dest;
}

ABSYS_API char* absys_str_stack_pop(struct absys_str_stack* str_stack) {
    char* str = absys_cstr_vec_pop(&str_stack->stack);
    absys_objpool_pop(&str_stack->objpool, strlen(str) + 1);
    return str;
}

ABSYS_API char* absys_str_stack_peek(struct absys_str_stack* str_stack) {
    char* str = absys_cstr_vec_get(&str_stack->stack, str_stack->stack.size - 1);
    return str;
}

ABSYS_API void absys_str_stack_del(struct absys_str_stack* str_stack) {
    absys_objpool_del(&str_stack->objpool);
    absys_cstr_vec_del(&str_stack->stack);
}
