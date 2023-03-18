#include "absys/test.h"
#include "vec/vec.h"
#include "dict/dict.h"
#include "trie/trie.h"
#include "set/set.h"

int main(int argc, char * argv[]) {
    suite vec = test_suite(NULL, "vec");
    test_case(vec, "vec", test_vec);
    suite dict = test_suite(NULL, "dict");
    test_case(dict, "dict", test_dict);
    suite trie = test_suite(NULL, "trie");
    test_case(trie, "trie", test_trie);
    suite set = test_suite(NULL, "set");
    test_case(set, "set", test_set);

    return test_run(argc, argv);
}
