#ifndef _ABSYS_TEST_H
#define _ABSYS_TEST_H

#include "absys/str.h"
#include "absys/color.h"
#include <stdio.h>
#include <string.h>
#include "absys/defs.h"

ABSYS_API extern struct absys_str _absys_test_buffer;
extern int number_total;
extern int number_passed;
extern int number_failed;
extern int number_skipped;
extern int number_todo;

#define _absys_test_wrap(block) do {\
	block\
} while(0)

#define assert_zero(a) assert_int_equal(a, 0)

#define _absys_assert_sprintf(LAB, FMTA, FMTB, VALA, VALB) absys_str_printf(&_absys_test_buffer, ABSYS_TAB ABSYS_RED "• Error: Expected %s " FMTA " to equal " FMTB ABSYS_RESET "\n\n" ABSYS_TAB ABSYS_GREEN "+ expected" ABSYS_RESET " " ABSYS_RED "- actual" ABSYS_RESET "\n\n" ABSYS_TAB ABSYS_GREEN "+ " FMTA ABSYS_RESET "\n" ABSYS_TAB ABSYS_RED "- " FMTB ABSYS_RESET "\n\n" ABSYS_TAB "at %s, line %d", LAB, VALA, VALB, VALA, VALB, __FILE__, __LINE__)

#define assert_int_equal(expected, actual) _absys_test_wrap(\
int _absys_expected = (expected);\
int _absys_actual = (actual);\
if(_absys_expected != _absys_actual) {\
    _absys_assert_sprintf("int", "%d", "%d", _absys_expected, _absys_actual);\
    return fail(_absys_test_buffer.data);\
})

#define assert_int_zero(actual) assert_int_equal(0, actual)

#define assert_uint_equal(expected, actual) _absys_test_wrap(\
unsigned int _absys_expected = (expected);\
unsigned int _absys_actual = (actual);\
if(_absys_expected != _absys_actual) {\
    _absys_assert_sprintf("uint", "%u", "%u", _absys_expected, _absys_actual);\
    return fail(_absys_test_buffer.data);\
})


#define assert_ptr_equal(expected, actual) _absys_test_wrap(\
void * _absys_expected = (expected);\
void * _absys_actual = (actual);\
if(_absys_expected != _absys_actual) {\
    if (!_absys_expected) {\
    	_absys_assert_sprintf("ptr", "%s", "%p", "NULL", _absys_actual);\
    }\
    else if (!_absys_actual) {\
    	_absys_assert_sprintf("ptr", "%p", "%s", _absys_expected, "NULL");\
    }\
    else {\
    	_absys_assert_sprintf("ptr", "%p", "%p", _absys_expected, _absys_actual);\
    }\
    return fail(_absys_test_buffer.data);\
})

#define assert_cstr_equal(expected, actual) _absys_test_wrap(\
	char * _absys_expected = (expected);\
	char * _absys_actual = (actual);\
	int _absys_failed = 0;\
	if (!_absys_expected) {\
		_absys_assert_sprintf("cstr", "%s", "%s", "NULL", _absys_actual);\
    		return fail(_absys_test_buffer.data);\
	}\
	else if (!_absys_actual) {\
		_absys_assert_sprintf("cstr", "%s", "%s", _absys_expected, "NULL");\
    		return fail(_absys_test_buffer.data);\
	}\
	else if(strcmp(_absys_expected, _absys_actual) != 0) {\
		_absys_assert_sprintf("cstr", "%s", "%s", _absys_expected, _absys_actual);\
    		return fail(_absys_test_buffer.data);\
	}\
)

#define assert_true(actual) assert_bool_true(actual)

#define assert_bool_true(actual) _absys_test_wrap(\
int _absys_actual = (actual);\
if(!_absys_actual) {\
    _absys_assert_sprintf("bool", "%s", "%s", "true", "false");\
    return fail(_absys_test_buffer.data);\
})

struct absys_test_suite {
    struct absys_test_suite * parent;
    char * name;
    char complete_name[256];
    struct absys_vec test_suites;
    struct absys_vec test_cases;
};

enum absys_test_result_type {
    TEST_RESULT_PASS,
    TEST_RESULT_FAIL,
    TEST_RESULT_SKIP,
    TEST_RESULT_TODO
};

struct absys_test_result {
    enum absys_test_result_type type;
    char * message;
};

struct absys_test_case {
    char * description;
    struct absys_test_result (*test)();
};

typedef struct absys_test_result test;

typedef struct absys_test_suite* suite;

#define ABSYS_TEST_ROOT "root"
#define ABSYS_TEST_PREFIX "------ "
#define ABSYS_TEST_SUFFIX ""
#define ABSYS_TEST_SEPARATOR " > "

ABSYS_API struct absys_test_suite * test_suite(struct absys_test_suite * parent, char * name);

ABSYS_API int test_case_id_gen();

ABSYS_API struct absys_test_case * test_case(struct absys_test_suite * parent, char * name, struct absys_test_result (*test)());

ABSYS_API struct absys_test_result pass();

ABSYS_API struct absys_test_result fail(char * diagnostic);

ABSYS_API struct absys_test_result skip();

ABSYS_API struct absys_test_result todo();

ABSYS_API int test_run(int argc, char * argv[]);

ABSYS_API void test_report_suite(char * complete_name);

ABSYS_API void test_report_case(struct absys_test_case * test_case, struct absys_test_result result);

ABSYS_API void test_report_results(long seed, double duration);

ABSYS_API struct absys_test_suite * test_suite_resolve(struct absys_test_suite * suite, char * name);

ABSYS_API void test_suite_del(struct absys_test_suite * suite);

#endif
