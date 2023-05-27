#ifndef __ABSYS_FILEBUF_h
#define __ABSYS_FILEBUF_h

#include "absys/vec.h"
#include "absys/defs.h"
#include "absys/buf.h"
#include <stdint.h>

// TODO: add flush strategy based on time
// TODO: automatically infer reasonable flush_size based on current resident set size

struct absys_filebuf {
	size_t flush_size;
	struct absys_buf buf;
	FILE* file_buf;		
};

ABSYS_API void absys_filebuf_init(struct absys_filebuf* filebuf, char* filepath, size_t flush_size);
ABSYS_API void absys_filebuf_exit(struct absys_filebuf* filebuf);
ABSYS_API void absys_filebuf_flush(struct absys_filebuf* filebuf);
ABSYS_API void absys_filebuf_update(struct absys_filebuf* filebuf);

#endif
