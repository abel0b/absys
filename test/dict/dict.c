#include "absys/dict.h"
#include "dict.h"

test test_dict(void) {
    struct absys_dict mydict;
    absys_dict_init(&mydict);
    for(int i = 0; i < mydict.numbuckets; ++i) {
    	assert_int_zero(mydict.sizes[i]);
    }

    int a = 42;
    int b = 1337;
    int c = 1024;

    absys_dict_set(&mydict, "foo", &a);
    assert_ptr_equal(&a, absys_dict_get(&mydict, "foo"));

    absys_dict_set(&mydict, "foo", &b);
    assert_ptr_equal(&b, absys_dict_get(&mydict, "foo"));

    absys_dict_set(&mydict, "", &c);
    assert_ptr_equal(&c, absys_dict_get(&mydict, ""));

    assert_ptr_equal(&b, absys_dict_get(&mydict, "foo"));

    absys_dict_exit(&mydict);

    return pass();
}
