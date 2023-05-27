#include "absys/vec.h"
#include "absys/buf.h"
#include "buf.h"

test test_buf(void) {
    struct absys_buf mybuf;
    absys_buf_init(&mybuf);
    int mydata[42];
    for(int i = 0; i < 42; i++) {
        mydata[i] = i;
    }
    absys_buf_write_end(&mybuf, (void*)mydata, sizeof(mydata)); 
    assert_int_equal(mybuf.size, sizeof(mydata));
    int i = 32;
    assert_int_equal(i, ((int*)mybuf.data)[i]);
    absys_buf_flush(&mybuf);
    assert_int_equal(mybuf.size, 0);
    absys_buf_exit(&mybuf);
    return pass();
}
