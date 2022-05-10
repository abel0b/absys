#include "inut/inut.h"
#include "vec/vec.h"

int main(int argc, char * argv[]) {
    suite vec = test_suite(NULL, "vec");
    test_case(vec, "vec", test_vec);

    return test_run(argc, argv);
}
