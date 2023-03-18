#include "absys/trie.h"
#include "trie.h"

test test_trie(void) {
	struct absys_trie mytrie;

	absys_trie_new(&mytrie);

	assert_int_equal(0, absys_trie_size(&mytrie));
	absys_trie_set(&mytrie, "foo", (void*)0x42);
	assert_int_equal(1, absys_trie_size(&mytrie));
	assert_ptr_equal((void*)0x42,  absys_trie_get(&mytrie, "foo"));
	absys_trie_set(&mytrie, "foo", (void*)0x42);
	assert_int_equal(1, absys_trie_size(&mytrie));
	assert_ptr_equal((void*)0x42,  absys_trie_get(&mytrie, "foo"));

	absys_trie_set(&mytrie, "yo", (void*)0x16);
	assert_int_equal(2, absys_trie_size(&mytrie));
	assert_ptr_equal((void*)0x42,  absys_trie_get(&mytrie, "foo"));
	assert_ptr_equal((void*)0x16,  absys_trie_get(&mytrie, "yo"));

	absys_trie_set(&mytrie, "foobar", (void*)0xdeadbeef);
	assert_int_equal(3, absys_trie_size(&mytrie));
	assert_ptr_equal((void*)0x16,  absys_trie_get(&mytrie, "yo"));
	assert_ptr_equal((void*)0x42,  absys_trie_get(&mytrie, "foo"));
	assert_ptr_equal((void*)0xdeadbeef,  absys_trie_get(&mytrie, "foobar"));

	absys_trie_set(&mytrie, "fogo", (void*)0xabe1);
	assert_int_equal(4, absys_trie_size(&mytrie));
	assert_ptr_equal((void*)0x16,  absys_trie_get(&mytrie, "yo"));
	assert_ptr_equal((void*)0x42,  absys_trie_get(&mytrie, "foo"));
	assert_ptr_equal((void*)0xdeadbeef,  absys_trie_get(&mytrie, "foobar"));
	assert_ptr_equal((void*)0xabe1,  absys_trie_get(&mytrie, "fogo"));

	absys_trie_set(&mytrie, "", (void*)0x007);
	assert_int_equal(5, absys_trie_size(&mytrie));
	assert_ptr_equal((void*)0x007,  absys_trie_get(&mytrie, ""));
	assert_ptr_equal((void*)0x16,  absys_trie_get(&mytrie, "yo"));
	assert_ptr_equal((void*)0x42,  absys_trie_get(&mytrie, "foo"));
	assert_ptr_equal((void*)0xdeadbeef,  absys_trie_get(&mytrie, "foobar"));
	assert_ptr_equal((void*)0xabe1,  absys_trie_get(&mytrie, "fogo"));

	struct absys_trie_it iter;
	char* key;
	void* value;	

	
	absys_trie_it_new(&iter, &mytrie);
	
	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("", key);

	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("fogo", key);

	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("yo", key);

	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("foo", key);
	
	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("foobar", key);
	
	assert_int_equal(0, absys_trie_it_next(&iter));

	absys_trie_it_del(&iter);


	absys_trie_it_new(&iter, &mytrie);
	
	assert(absys_trie_it_next_prefix(&iter, ""));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("", key);

	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("fogo", key);

	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("yo", key);

	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("foo", key);
	
	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("foobar", key);
	
	assert_int_equal(0, absys_trie_it_next(&iter));

	absys_trie_it_del(&iter);


	absys_trie_it_new(&iter, &mytrie);
	assert(absys_trie_it_next_prefix(&iter, "fogo"));
	
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("fogo", key);

	assert_int_equal(0, absys_trie_it_next(&iter));

	absys_trie_it_del(&iter);
	

	absys_trie_it_new(&iter, &mytrie);
	assert(absys_trie_it_next_prefix(&iter, "foo"));
	
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("foo", key);

	assert_int_equal(1, absys_trie_it_next(&iter));
	absys_trie_it_get(&iter, &key, &value);
	assert_cstr_equal("foobar", key);

	assert_int_equal(0, absys_trie_it_next(&iter));

	absys_trie_it_del(&iter);

	
	absys_trie_del(&mytrie);

	return pass();
}
