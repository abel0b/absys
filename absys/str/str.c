#include "absys/str.h"
#include "absys/log.h"
#include "absys/mem.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "absys/utils.h"

absys_vec_impl(struct absys_str, str)

ABSYS_API void absys_str_new(struct absys_str* str) {
    str->len = 0;
    str->cap = 8;
    str->data = absys_malloc(sizeof(str->data[0]) * str->cap);
    str->data[0] = '\0';
}

ABSYS_API void absys_str_catf(struct absys_str* str, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    while(str->cap < str->len + len + 1) {
        str->cap = (str->cap)? 2 * str->cap : 8;
        str->data = absys_realloc(str->data, sizeof(str->data[0]) * str->cap);
    }

    va_start(args, fmt);
    vsnprintf(&str->data[str->len], len + 1, fmt, args);
    va_end(args);
    str->len += len;
}

ABSYS_API void absys_str_printf(struct absys_str* str, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    while(str->cap < len + 1) {
        str->cap = (str->cap)? 2 * str->cap : 8;
        str->data = absys_realloc(str->data, sizeof(str->data[0]) * str->cap);
    }

    va_start(args, fmt);
    vsnprintf(str->data, len + 1, fmt, args);
    va_end(args);
    str->len += len;
}


ABSYS_API void absys_str_cat(struct absys_str* str, const char* src) {
    int len = strlen(src);
    while(str->cap < str->len + len + 1) {
        str->cap = (str->cap)? 2 * str->cap : 8;
        str->data = absys_realloc(str->data, sizeof(str->data[0]) * str->cap);
    }
    strcpy(&str->data[str->len], src);
    str->len += len;
}

ABSYS_API void absys_str_resize(struct absys_str* str, long int len) {
    if (len + 1 > str->cap) {
        str->cap = len + 1;
        str->data = absys_realloc(str->data, sizeof(str->data[0]) * str->cap);
    }
    str->len = len;
    str->data[len] = '\0';
}

ABSYS_API void absys_str_flush(struct absys_str* str) {
    str->len = 0;
    str->data[0] = '\0';
}

ABSYS_API void absys_str_del(struct absys_str* str) {
    if (str->data) {
        absys_free(str->data);
    }
}
