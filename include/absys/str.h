#ifndef ABSYSSTR__H
#define ABSYSSTR__H

#include "absys/vec.h"
#include "absys/defs.h"

struct absys_str {
    char* data;
    int len;
    int cap;
};

ABSYS_API void absys_str_new(struct absys_str* str);
ABSYS_API void absys_str_del(struct absys_str* str);
ABSYS_API void absys_str_printf(struct absys_str* str, const char* fmt, ...);
ABSYS_API void absys_str_catf(struct absys_str* str, const char* fmt, ...);
ABSYS_API void absys_str_cat(struct absys_str* str, const char* src);
ABSYS_API void absys_str_resize(struct absys_str* str, long int len);
ABSYS_API void absys_str_flush(struct absys_str* str);

absys_vec_decl(struct absys_str, str)

#endif
