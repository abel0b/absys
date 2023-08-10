#include "absys/test.h"
#include "absys/queue.h"
#include "queue.h"

struct foo {
	int a;
	int b;
};

absys_queue_decl(struct foo, foo);
absys_queue_impl(struct foo, foo);

test test_queue(void) {
	struct absys_queue myqueue;
	absys_queue_init(&myqueue, sizeof(int));
	assert_true(absys_queue_empty(&myqueue));

	int val = 42;
	absys_queue_enqueue(&myqueue, &val);
	assert_true(!absys_queue_empty(&myqueue));
	assert_int_equal(absys_queue_size(&myqueue), 1);

	int val1;
	absys_queue_dequeue(&myqueue, &val1);
	assert_int_equal(absys_queue_size(&myqueue), 0);
	assert_int_equal(val, val1);
	assert_true(absys_queue_empty(&myqueue));

	for (int i = 0; i < ABSYS_QUEUE_UNROLL_FACTOR * 64; ++i) {
		assert_int_equal(i * 3, absys_queue_size(&myqueue));
		int cursize = absys_queue_size(&myqueue);

		for(int j = 0; j < 3; ++j) {
			val = i * 3 + j;
			absys_queue_enqueue(&myqueue, &val);
			assert_int_equal(cursize + j + 1, absys_queue_size(&myqueue));
		}
	}
	
	for (int i = 0; i < ABSYS_QUEUE_UNROLL_FACTOR * 64; ++i) {
		for(int j = 0; j < 3; ++j) {
			val = -1;
			absys_queue_dequeue(&myqueue, &val);
			assert_int_equal(i * 3 + j, val);
		}
	}	

	assert_true(absys_queue_empty(&myqueue));
	absys_queue_exit(&myqueue);

	struct absys_foo_queue myfooqueue;
	absys_foo_queue_init(&myfooqueue);

	struct foo f1 = { 1, 2 };
	struct foo f2 = { 3, 4 };
	struct foo f3 = { 5, 6 };

	assert_true(absys_foo_queue_empty(&myfooqueue));
	absys_foo_queue_enqueue(&myfooqueue, f1);
	assert_int_equal(absys_foo_queue_size(&myfooqueue), 1);
	absys_foo_queue_enqueue(&myfooqueue, f2);
	assert_int_equal(absys_foo_queue_size(&myfooqueue), 2);
	absys_foo_queue_enqueue(&myfooqueue, f3);
	assert_int_equal(absys_foo_queue_size(&myfooqueue), 3);

	struct foo f4;
	f4 = absys_foo_queue_dequeue(&myfooqueue);
	assert_int_equal(absys_foo_queue_size(&myfooqueue), 2);
	assert_int_equal(f4.a, 1);
	assert_int_equal(f4.b, 2);

	f4 = absys_foo_queue_dequeue(&myfooqueue);
	assert_int_equal(absys_foo_queue_size(&myfooqueue), 1);
	assert_int_equal(f4.a, 3);
	assert_int_equal(f4.b, 4);

	f4 = absys_foo_queue_dequeue(&myfooqueue);
	assert_int_equal(absys_foo_queue_size(&myfooqueue), 0);
	assert_int_equal(f4.a, 5);
	assert_int_equal(f4.b, 6);

	absys_foo_queue_exit(&myfooqueue);

	return pass();
}
