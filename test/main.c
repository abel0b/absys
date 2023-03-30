#include "absys/test.h"
#include "buf/buf.h"
#include "dict/dict.h"
#include "vec/vec.h"
#include "set/set.h"
#include "trie/trie.h"
#include "hook/hook.h"
#include "filebuf/filebuf.h"
#include "bits/bits.h"

int main(int argc, char * argv[]) {
	suite buf = test_suite(NULL, "buf");
	test_case(buf, "buf", test_buf);
	suite dict = test_suite(NULL, "dict");
	test_case(dict, "dict", test_dict);
	suite vec = test_suite(NULL, "vec");
	test_case(vec, "vec", test_vec);
	suite set = test_suite(NULL, "set");
	test_case(set, "set", test_set);
	suite trie = test_suite(NULL, "trie");
	test_case(trie, "trie", test_trie);
	suite hook = test_suite(NULL, "hook");
	test_case(hook, "hook", test_hook);
	suite filebuf = test_suite(NULL, "filebuf");
	test_case(filebuf, "filebuf", test_filebuf);
	suite bits = test_suite(NULL, "bits");
	test_case(bits, "bits", test_bits);
	return test_run(argc, argv);
}
