#include "absys/buf.h"
#include "absys/mem.h"
#include <string.h>
#include "absys/utils.h"

ABSYS_API void absys_buf_new(struct absys_buf* buf) {
    buf->size = 0;
    buf->capacity = 1024;
    buf->data = absys_malloc(buf->capacity);
}

ABSYS_API void absys_buf_del(struct absys_buf* buf) {
    absys_free(buf->data);
}

ABSYS_API void absys_buf_resize(struct absys_buf* buf, size_t size) {
    if (size > buf->capacity) {
        buf->capacity = 2 * buf->capacity + size;
        buf->data = absys_realloc(buf->data, buf->capacity);
    }
    buf->size = size;
}

ABSYS_API void absys_buf_write_end(struct absys_buf* buf, void* data, size_t size) {
    if (buf->size + size > buf->capacity) {
        buf->capacity = 2 * buf->capacity + size;
        buf->data = absys_realloc(buf->data, buf->capacity);
    }
    void* dest = memcpy(((char*)buf->data) + buf->size, data, size);
    absys_unused(dest);
    buf->size += size;
}

ABSYS_API size_t absys_buf_size(struct absys_buf* buf) {
    return buf->size;
}

ABSYS_API void* absys_buf_data(struct absys_buf* buf) {
    return buf->data;
}

ABSYS_API void absys_buf_flush(struct absys_buf* buf) {
    buf->size = 0;
    // TODO: shrink buffer size
}


