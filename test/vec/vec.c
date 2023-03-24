#include "absys/vec.h"
#include "vec.h"

test test_vec(void) {
    struct absys_vec myvec;
    absys_vec_new(&myvec, sizeof(int));
    assert_true(absys_vec_empty(&myvec));
    assert_int_equal(0, myvec.size);
    assert_uint_equal(sizeof(0), myvec.elem_size);
    int val = 42;
    absys_vec_push(&myvec, &val);
    assert_int_equal(1, myvec.size);
    val = 1024;
    absys_vec_push(&myvec, &val);
    int val2;
    absys_vec_peek(&myvec, &val2);
    assert_int_equal(1024, val2);
    assert_int_equal(2, myvec.size);
    assert_int_equal(42, *(int *)absys_vec_get(&myvec, 0));
    assert_int_equal(1024, *(int *)absys_vec_get(&myvec, 1));
    assert_int_equal(2, myvec.size);
    absys_vec_pop(&myvec, &val);
    assert_int_equal(1024, val);
    absys_vec_pop(&myvec, &val);
    assert_int_equal(42, val);
    assert_int_equal(0, myvec.size);
    absys_vec_del(&myvec);
    return pass();
}
