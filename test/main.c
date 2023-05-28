#include "absys/test.h"
#include "bits/bits.h"
#include "buf/buf.h"
#include "dict/dict.h"
#include "filebuf/filebuf.h"
#include "hook/hook.h"
#include "set/set.h"
#include "trie/trie.h"
#include "vec/vec.h"
#include "list/list.h"
#include "queue/queue.h"

int main(int argc, char * argv[]) {
	suite bits = test_suite(NULL, "bits");
	test_case(bits, "bits", test_bits);
	suite buf = test_suite(NULL, "buf");
	test_case(buf, "buf", test_buf);
	suite dict = test_suite(NULL, "dict");
	test_case(dict, "dict", test_dict);
	suite filebuf = test_suite(NULL, "filebuf");
	test_case(filebuf, "filebuf", test_filebuf);
	suite hook = test_suite(NULL, "hook");
	test_case(hook, "hook", test_hook);
	suite set = test_suite(NULL, "set");
	test_case(set, "set", test_set);
	suite trie = test_suite(NULL, "trie");
	test_case(trie, "trie", test_trie);
	suite vec = test_suite(NULL, "vec");
	test_case(vec, "vec", test_vec);
	suite list = test_suite(NULL, "list");
	test_case(list, "list", test_list);
	suite queue = test_suite(NULL, "queue");
	test_case(queue, "queue", test_queue);
	return test_run(argc, argv);
}
