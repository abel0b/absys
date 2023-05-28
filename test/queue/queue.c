#include "absys/test.h"
#include "absys/queue.h"
#include "queue.h"

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
	return pass();
}
