#include "absys/filebuf.h"
#include "absys/utils.h"

ABSYS_API void absys_filebuf_new(struct absys_filebuf* filebuf, char* filepath, size_t flush_size) {
	absys_buf_new(&filebuf->buf);
	filebuf->flush_size = flush_size;
	filebuf->file_buf = fopen(filepath, "wb");
	absys_assert(filebuf->file_buf);
}

ABSYS_API void absys_filebuf_del(struct absys_filebuf* filebuf) {
	absys_filebuf_flush(filebuf);
	absys_buf_del(&filebuf->buf);
	int rc = fclose(filebuf->file_buf);
	absys_assert(rc == 0);
}

ABSYS_API void absys_filebuf_flush(struct absys_filebuf* filebuf) {
	if (filebuf->buf.size) {
		int wsize = fwrite(absys_buf_data(&filebuf->buf), absys_buf_size(&filebuf->buf), 1, filebuf->file_buf);
		absys_assert(wsize == 1);
		int rc = fflush(filebuf->file_buf);
		absys_assert(rc == 0);
		absys_buf_flush(&filebuf->buf);
	}
}

ABSYS_API void absys_filebuf_update(struct absys_filebuf* filebuf) {
	if (filebuf->buf.size > filebuf->flush_size) {
		absys_filebuf_flush(filebuf);
	}
}
