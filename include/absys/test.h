#ifndef __ABSYS_TEST_h
#ifndef __ABSYS_TEST_h

#include <stdio.h>

int _absys_test_strcmp(const char* s1, const char* s2);

// TODO: dynamic string size
// TODO: handle name conflicts
#define INUT_MAX_STR 4096
extern char _absys_test_buffer[INUT_MAX_STR];

#define absys_test_typecheck(type,var) { typedef void (*type_t)(type); type_t tmp = (type_t)0; if(0) tmp(var);}

#define _absys_test_wrap(block) do {\
	block\
} while(0)

#define assert_zero(a) assert_int_equal(a, 0)

#define _absys_test_assert_sprintf(LAB, FMTA, FMTB, VALA, VALB) sprintf(_absys_test_buffer, INUT_TAB INUT_RED "• Error: Expected %s " FMTA " to equal " FMTB INUT_RESET "\n\n" INUT_TAB INUT_GREEN "+ expected" INUT_RESET " " INUT_RED "- actual" INUT_RESET "\n\n" INUT_TAB INUT_GREEN "+ " FMTA INUT_RESET "\n" INUT_TAB INUT_RED "- " FMTB INUT_RESET "\n\n" INUT_TAB "at %s, line %d", LAB, VALA, VALB, VALA, VALB, __FILE__, __LINE__)

#define assert_int_equal(expected, actual) _absys_test_wrap(\
int _absys_test_expected = (expected);\
int _absys_test_actual = (actual);\
if(_absys_test_expected != _absys_test_actual) {\
    _absys_test_assert_sprintf("int", "%d", "%d", _absys_test_expected, _absys_test_actual);\
    return fail(_absys_test_buffer);\
})


#define assert_int_zero(actual) assert_int_equal(0, actual)

#define assert_uint_equal(expected, actual) _absys_test_wrap(\
unsigned int _absys_test_expected = (expected);\
unsigned int _absys_test_actual = (actual);\
if(_absys_test_expected != _absys_test_actual) {\
    _absys_test_assert_sprintf("uint", "%u", "%u", _absys_test_expected, _absys_test_actual);\
    return fail(_absys_test_buffer);\
})


#define assert_ptr_equal(expected, actual) _absys_test_wrap(\
void * _absys_test_expected = (expected);\
void * _absys_test_actual = (actual);\
if(_absys_test_expected != _absys_test_actual) {\
    if (!_absys_test_expected) {\
    	_absys_test_assert_sprintf("ptr", "%s", "%p", "NULL", _absys_test_actual);\
    }\
    else if (!_absys_test_actual) {\
    	_absys_test_assert_sprintf("ptr", "%p", "%s", _absys_test_expected, "NULL");\
    }\
    else {\
    	_absys_test_assert_sprintf("ptr", "%p", "%p", _absys_test_expected, _absys_test_actual);\
    }\
    return fail(_absys_test_buffer);\
})

#define assert_cstr_equal(expected, actual) _absys_test_wrap(\
	char * _absys_test_expected = (expected);\
	char * _absys_test_actual = (actual);\
	int _absys_test_failed = 0;\
	if (!_absys_test_expected) {\
		_absys_test_assert_sprintf("cstr", "%s", "%s", "NULL", _absys_test_actual);\
    		return fail(_absys_test_buffer);\
	}\
	else if (!_absys_test_actual) {\
		_absys_test_assert_sprintf("cstr", "%s", "%s", _absys_test_expected, "NULL");\
    		return fail(_absys_test_buffer);\
	}\
	else if(_absys_test_strcmp(_absys_test_expected, _absys_test_actual) != 0) {\
		_absys_test_assert_sprintf("cstr", "%s", "%s", _absys_test_expected, _absys_test_actual);\
    		return fail(_absys_test_buffer);\
	}\
)

#define assert(actual) assert_bool(actual)

#define assert_bool(actual) _absys_test_wrap(\
int _absys_test_actual = (actual);\
if(!_absys_test_actual) {\
    _absys_test_assert_sprintf("bool", "%s", "%s", "true", "false");\
    return fail(_absys_test_buffer);\
})

#define INUT_TAB "       "

#define INUT_TEST_ROOT "root"
#define INUT_TEST_PREFIX "------ "
#define INUT_TEST_SUFFIX ""
#define INUT_TEST_SEPARATOR " > "

struct TestSuite * test_suite(struct TestSuite * parent, char * name);

int test_case_id_gen();

struct TestCase * test_case(struct TestSuite * parent, char * name, struct TestResult (*test)());

struct TestResult pass();

struct TestResult fail(char * diagnostic);

struct TestResult skip();

struct TestResult todo();

int test_run(int argc, char * argv[]);

extern int number_total;
extern int number_passed;
extern int number_failed;
extern int number_skipped;
extern int number_todo;

void
test_report_suite(char * complete_name);

void
test_report_case(struct TestCase * test_case, struct TestResult result);

void
test_report_results(long seed, long duration);

struct TestSuite {
    struct TestSuite * parent;
    char * name;
    char complete_name[256];
    struct Array * test_suites;
    struct Array * test_cases;
};

struct TestSuiteIterator {
    struct Stack * stack;
    struct TestSuite * begin;
    struct TestSuite * current;
};

enum TestResultType {
    TEST_RESULT_PASS,
    TEST_RESULT_FAIL,
    TEST_RESULT_SKIP,
    TEST_RESULT_TODO
};

struct TestResult {
    enum TestResultType type;
    char * message;
};

struct TestCase {
    char * description;
    struct TestResult (*test)();
};

typedef struct TestResult test;

typedef struct TestSuite * suite;

struct TestSuite * test_suite_resolve(struct TestSuite * suite, char * name);

void test_case_destroy(struct TestCase * test);

struct TestSuiteIterator * test_suite_it_make (struct TestSuite * suite);

void test_suite_it_next (struct TestSuiteIterator * suite_it);

int test_suite_it_done (struct TestSuiteIterator * suite_it);

void test_suite_it_destroy(struct TestSuiteIterator * suite);

struct TestSuite * test_suite_it_get (struct TestSuiteIterator * suite_it);

void test_suite_destroy(struct TestSuite * suite);

#endif
