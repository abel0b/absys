add_library(
    inut
    test_report.c
    test_suite.c
    test.c
)

target_link_libraries(
    inut
    array
)