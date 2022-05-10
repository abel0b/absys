#ifndef INUT_ASSERT_H
#define INUT_ASSERT_H

#include "inut/test_report.h"
#include "inut/defs.h"
#include <stdio.h>

// TODO: dynamic string size
#define INUT_MAX_STR 4096

#define inut_typecheck(type,var) { typedef void (*type_t)(type); type_t tmp = (type_t)0; if(0) tmp(var);}

extern char inut_buffer[INUT_MAX_STR];

#define assert_zero(a) assert_int_equal(a, 0)

#define assert_sprintf(LAB, FMTA, FMTB, VALA, VALB) sprintf(inut_buffer, INUT_TAB INUT_RED "• Error: Expected %s " FMTA " to equal " FMTB INUT_RESET "\n\n" INUT_TAB INUT_GREEN "+ expected" INUT_RESET " " INUT_RED "- actual" INUT_RESET "\n\n" INUT_TAB INUT_GREEN "+ " FMTA INUT_RESET "\n" INUT_TAB INUT_RED "- " FMTB INUT_RESET "\n\n" INUT_TAB "at %s, line %d", LAB, VALA, VALB, VALA, VALB, __FILE__, __LINE__)

#define assert_int_equal(a, b) if(a!=b) {\
    inut_typecheck(int, a);\
    inut_typecheck(int, b);\
    assert_sprintf("integer", "%d", "%d", (int)a, (int)b);\
    return fail(inut_buffer);\
}

#define assert_uint_equal(a, b) if(a!=b) {\
    inut_typecheck(unsigned int, a);\
    inut_typecheck(unsigned int, b);\
    assert_sprintf("unsigned integer", "%u", "%u", (unsigned int)a, (unsigned int)b);\
    return fail(inut_buffer);\
}

#define assert_ptr_equal(a, b) if(a != b) {\
    if (!a) {\
    	assert_sprintf("pointer", "%s", "%p", "NULL", b);\
    }\
    else {\
    	assert_sprintf("pointer", "%p", "%s", a, "NULL");\
    }\
    return fail(inut_buffer);\
}

#define assert(a) assert_boolean(a)

#define assert_boolean(a) if(!a) {\
    assert_sprintf("boolean", "%s", "%s", "false", "true");\
    return fail(inut_buffer);\
}

#endif

