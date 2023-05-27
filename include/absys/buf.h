#ifndef __ABSYS_BUF_h
#define __ABSYS_BUF_h

#include "absys/vec.h"
#include "absys/defs.h"
#include <stdint.h>

struct absys_buf {
    void * data;
    size_t size;
    size_t capacity;
};

ABSYS_API void absys_buf_init(struct absys_buf* buf);
ABSYS_API void absys_buf_exit(struct absys_buf* buf);
ABSYS_API void absys_buf_write_end(struct absys_buf* buf, void* data, size_t size);
ABSYS_API size_t absys_buf_size(struct absys_buf* buf);
ABSYS_API void* absys_buf_data(struct absys_buf* buf);
ABSYS_API void absys_buf_resize(struct absys_buf* buf, size_t size);
ABSYS_API void absys_buf_flush(struct absys_buf* buf);

#endif
