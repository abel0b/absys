#include "absys/test.h"
#include "vec/vec.h"
#include "dict/dict.h"
#include "trie/trie.h"
#include "set/set.h"
#include "buf/buf.h"
#include "filebuf/filebuf.h"

int main(int argc, char * argv[]) {
    suite vec = test_suite(NULL, "vec");
    test_case(vec, "vec", test_vec);
    suite dict = test_suite(NULL, "dict");
    test_case(dict, "dict", test_dict);
    suite trie = test_suite(NULL, "trie");
    test_case(trie, "trie", test_trie);
    suite set = test_suite(NULL, "set");
    test_case(set, "set", test_set);
    suite buf = test_suite(NULL, "buf");
    test_case(buf, "buf", test_buf);
    suite filebuf = test_suite(NULL, "filebuf");
    test_case(filebuf, "filebuf", test_filebuf);
    return test_run(argc, argv);
}
