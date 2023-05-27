#include "absys/set.h"
#include "set.h"

test test_set(void) {
    struct absys_cstr_set myset;
    absys_cstr_set_init(&myset);
    assert_int_equal(0, myset.size);
    assert_int_equal(true, absys_cstr_set_empty(&myset));
    assert_int_equal(0, myset.size);
    absys_cstr_set_add(&myset, "aa");
    assert_int_equal(1, myset.size);
    absys_cstr_set_add(&myset, "aab");
    assert_int_equal(2, myset.size);
    absys_cstr_set_add(&myset, "aab");
    assert_int_equal(2, myset.size);
    absys_cstr_set_add(&myset, "aac");
    assert_int_equal(3, myset.size);

    absys_cstr_set_exit(&myset);
    return pass();
}
