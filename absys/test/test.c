#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "absys/test.h"
#include "absys/time.h"

struct absys_str _absys_test_buffer;

struct absys_test_suite * test_root = NULL;

int id_count = 0;
int number_total = 0;
int number_passed = 0;
int number_failed = 0;
int number_skipped = 0;
int number_todo = 0;

ABSYS_API struct absys_test_result pass() {
    return (struct absys_test_result) {TEST_RESULT_PASS, NULL};
}

ABSYS_API struct absys_test_result fail (char * diagnostic) {
    return (struct absys_test_result) {TEST_RESULT_FAIL, diagnostic};
}

ABSYS_API struct absys_test_result skip () {
    return (struct absys_test_result) {TEST_RESULT_SKIP, NULL};
}

ABSYS_API struct absys_test_result todo () {
    return (struct absys_test_result) {TEST_RESULT_TODO, NULL};
}

ABSYS_API void test_init () {
    test_root = malloc (sizeof (struct absys_test_suite));
    test_root->parent = test_root;
    test_root->name = ABSYS_TEST_ROOT;
    strcpy(test_root->complete_name, "\0");
    absys_vec_init(&test_root->test_suites, sizeof(struct absys_test_suite));
    absys_vec_init(&test_root->test_cases, sizeof(struct absys_test_case));
    absys_str_init(&_absys_test_buffer);
}

ABSYS_API struct absys_test_suite * test_suite(struct absys_test_suite * suite, char * name) {
    if (test_root == NULL) {
        test_init();
    }

    struct absys_test_suite * parent_suite = (suite == NULL)? test_root : suite;

    struct absys_test_suite new_suite;
    new_suite.parent = parent_suite;
    new_suite.name = name;
    strcpy(new_suite.complete_name, "\0");
    absys_vec_init(&new_suite.test_suites, sizeof(struct absys_test_suite));
    absys_vec_init(&new_suite.test_cases, sizeof(struct absys_test_case));
    absys_vec_push(&parent_suite->test_suites, (void*)&new_suite);
    return (struct absys_test_suite*)absys_vec_last(&parent_suite->test_suites);
}

ABSYS_API struct absys_test_case * test_case(struct absys_test_suite * suite, char * description, struct absys_test_result (*test)()) {
    struct absys_test_suite * parent_suite = (suite == NULL)? test_root : suite;
    
    struct absys_test_case test_case;
    test_case.description = description;
    test_case.test = test;
    absys_vec_push(&parent_suite->test_cases, (void*)&test_case);
    return absys_vec_last(&parent_suite->test_cases);
}

ABSYS_API int test_run(int argc, char * argv[]) {
    struct absys_test_suite * suite = test_root;
    double t1, t2;

    long seed = 0;
    int opt;
    int seed_arg = 0;

    int i = 1;
    while(i<argc) {
        if (strcmp(argv[i], "-s") == 0) {
	    ++i;
	    seed_arg = 1;
            seed = atol(argv[i]);
	}
	else {
	    fprintf(stderr, "error: unknown option '%s'\n", argv[i]);
	    exit(1);
	}
	++i;
    }

    t1 = absys_get_wtime();
    if (!seed_arg) {
        seed = t1;
    }

    struct absys_ptr_vec stack;
    absys_ptr_vec_init(&stack);
    absys_ptr_vec_push(&stack, (void*) suite);
    
    while(!absys_ptr_vec_empty(&stack)) {
        struct absys_test_suite* isuite = (struct absys_test_suite*) absys_ptr_vec_pop(&stack);
        if (strcmp(isuite->name, ABSYS_TEST_ROOT) != 0) {
            if (strcmp(isuite->parent->name, ABSYS_TEST_ROOT) != 0) {
                strcat(isuite->complete_name, isuite->parent->complete_name);
                strcat(isuite->complete_name, ABSYS_TEST_SEPARATOR);
            }

            strcat(isuite->complete_name, isuite->name);

            if (!absys_vec_empty(&isuite->test_cases)) {
                test_report_suite(isuite->complete_name);
            }
        }

        for(int i = 0; i < absys_vec_size(&isuite->test_cases); ++ i) {
            struct absys_test_case * test = (struct absys_test_case*) absys_vec_get(&isuite->test_cases, i);
            test_report_case(test, test->test());
        }

        for(int ii = 0; ii < absys_vec_size(&isuite->test_suites); ++ii) {
            absys_ptr_vec_push(
                &stack,
                (void*) absys_vec_get(&isuite->test_suites, ii)
            );
        }
    }
    absys_ptr_vec_exit(&stack);

    t2 = absys_get_wtime();
    double elapsed = t2 - t1;

    test_report_results(seed, elapsed);
    test_suite_exit(test_root);
    
    if (number_failed) {
        return 1;
    }
    return 0;
}

ABSYS_API void
test_report_suite(char * complete_name) {
    printf (ABSYS_BOLD ABSYS_TEST_PREFIX "%s\n" ABSYS_RESET, complete_name);
}

ABSYS_API void
test_report_case(struct absys_test_case * test_case, struct absys_test_result result) {
    number_total ++;
    switch(result.type) {
        case TEST_RESULT_PASS:
            printf (ABSYS_WHITE_FG_GREEN " PASS " ABSYS_RESET);
            number_passed ++;
            break;
        case TEST_RESULT_FAIL:
            printf (ABSYS_WHITE_FG_RED " FAIL " ABSYS_RESET);
            number_failed ++;
            break;
        case TEST_RESULT_TODO:
            printf (ABSYS_WHITE_FG_BLUE " TODO " ABSYS_RESET);
            number_todo ++;
            break;
        case TEST_RESULT_SKIP:
            printf (ABSYS_WHITE_FG_YELLOW " SKIP " ABSYS_RESET);
            number_todo ++;
            break;
        default:
            break;
    }
    printf(" %s\n", test_case->description);
    if (result.message != NULL) {
        printf("\n%s\n\n", result.message);
    }
}

ABSYS_API void
test_report_progress_bar() {
    if (number_passed == number_total) return;
    int progress_pass = (float)number_passed / (float)number_total * 26;
    if (number_passed && progress_pass == 0) {
        progress_pass = 1;
    }

    int progress_fail = (float)number_failed / (float)number_total * 26;
    if (number_failed && progress_fail == 0) {
        progress_fail = 1;
    }

    int progress_todo = (float)number_todo / (float)number_total * 26;
    if (number_todo && progress_todo == 0) {
        progress_todo = 1;
    }

    int progress_skip = (float)number_skipped/ (float)number_total * 26;
    if (number_skipped && progress_skip == 0) {
        progress_skip = 1;
    }

    for(int i = 0; i < progress_pass; i++) {
        printf(ABSYS_GREEN "▄" ABSYS_RESET);
    }
    for(int i = 0; i < progress_fail; i++) {
        printf(ABSYS_RED "▄" ABSYS_RESET);
    }
    for(int i = 0; i < progress_todo; i++) {
        printf(ABSYS_BLUE "▄" ABSYS_RESET);
    }
    for(int i = 0; i < progress_skip; i++) {
        printf(ABSYS_YELLOW "▄" ABSYS_RESET);
    }
    printf("\n");
}

ABSYS_API void
test_report_results(long seed, double duration) {
    printf("• done in %.2fs •\n\n", duration);

    if (number_passed) {
        printf (ABSYS_GREEN "%d of %d tests passed" ABSYS_RESET "\n", number_passed, number_total);
    }
    if (number_failed) {
        printf (ABSYS_RED "%d of %d tests failed" ABSYS_RESET "\n", number_failed, number_total);
    }
    if (number_todo) {
        printf (ABSYS_BLUE "%d of %d tests todo" ABSYS_RESET "\n", number_todo, number_total);
    }
    if (number_skipped) {
        printf (ABSYS_YELLOW "%d of %d tests skipped" ABSYS_RESET "\n", number_skipped, number_total);
    }

    test_report_progress_bar();

    printf("\nrandomized with seed " ABSYS_BOLD "%ld" ABSYS_RESET "\n", seed);
}

ABSYS_API struct absys_test_suite * test_suite_resolve(struct absys_test_suite * suite, char * name) {
    struct absys_ptr_vec stack;
    absys_ptr_vec_init(&stack);
    absys_ptr_vec_push(&stack, (void*) suite);
    
    while(!absys_ptr_vec_empty(&stack)) {
        suite = (struct absys_test_suite*) absys_ptr_vec_pop(&stack);

        if (strcmp(suite->name, name) == 0) {
            absys_ptr_vec_exit(&stack);
            return suite;
        }

        for(int ii = 0; ii < absys_vec_size(&suite->test_suites); ++ii) {
            absys_ptr_vec_push(
                &stack,
                (void*) absys_vec_get(&suite->test_suites, ii)
            );
        }
    }
    absys_ptr_vec_exit(&stack);
    return NULL;
}

ABSYS_API void test_suite_exit(struct absys_test_suite * suite) {
   for(int i = 0; i < absys_vec_size(&suite->test_suites); ++ i) {
        test_suite_exit((struct absys_test_suite*) absys_vec_get(&suite->test_suites, i));
   }
   absys_vec_exit(&suite->test_suites);
   absys_vec_exit(&suite->test_cases);
}
