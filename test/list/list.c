#include "absys/test.h"
#include "absys/list.h"
#include "list.h"

test test_list(void) {
	struct absys_list mylist;
	absys_list_new(&mylist, sizeof(int));
	assert_true(absys_list_empty(&mylist));

	int val = 42;
	absys_list_push(&mylist, &val);
	assert_true(!absys_list_empty(&mylist));
	assert_int_equal(absys_list_size(&mylist), 1);
	int val1;
	absys_list_pop(&mylist, &val1);
	assert_int_equal(absys_list_size(&mylist), 0);
	assert_int_equal(val, val1);

	assert_true(absys_list_empty(&mylist));
	for (int i = 0; i < ABSYS_LIST_UNROLL_FACTOR * 64; ++i) {
		assert_int_equal(i * 3, absys_list_size(&mylist));
		int cursize = absys_list_size(&mylist);

		for(int j = 0; j < 3; ++j) {
			val = i * 3 + j;
			absys_list_push(&mylist, &val);
			assert_int_equal(cursize + j + 1, absys_list_size(&mylist));
		}
	}
		
	int tmp;
	for (int i = 0; i < ABSYS_LIST_UNROLL_FACTOR * 64; ++i) {
		int cursize = absys_list_size(&mylist);
		for(int j = 0; j < 3; ++j) {
			absys_list_pop(&mylist, &tmp);
			assert_int_equal(i * 3 + j, tmp);
			assert_int_equal(cursize - j - 1, absys_list_size(&mylist));
		}
	}
	assert_true(absys_list_empty(&mylist));

	absys_list_del(&mylist);
	return pass();
}
