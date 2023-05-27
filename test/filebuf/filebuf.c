#include "absys/filebuf.h"
#include "filebuf.h"

test test_filebuf(void) {
    struct absys_filebuf myfilebuf;
    absys_filebuf_init(&myfilebuf, "myfilebuf.bin", 200e6);
    absys_filebuf_flush(&myfilebuf);
    int foo = 42;
    absys_buf_write_end(&myfilebuf.buf, (void*)&foo, sizeof(int));
    absys_filebuf_flush(&myfilebuf);
    absys_filebuf_exit(&myfilebuf);
    return pass();
}
