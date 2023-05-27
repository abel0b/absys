#ifndef ABSYSSTRSTACK__H
#define ABSYSSTRSTACK__H

#include "absys/objpool.h"
#include "absys/vec.h"
#include "absys/defs.h"

struct absys_str_stack {
    struct absys_objpool objpool;
    struct absys_cstr_vec stack;
};

ABSYS_API void absys_str_stack_init(struct absys_str_stack* strstack);

ABSYS_API char* absys_str_stack_push(struct absys_str_stack* str_stack, const char* str);

ABSYS_API char* absys_str_stack_pushf(struct absys_str_stack* strstack, const char * fmt, ...);

ABSYS_API char* absys_str_stack_pop(struct absys_str_stack* strstack);

ABSYS_API char* absys_str_stack_peek(struct absys_str_stack* strstack);

ABSYS_API void absys_str_stack_exit(struct absys_str_stack* strstack);

#endif
