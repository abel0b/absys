set -e

test=$1

cd test

mkdir $test

cat << EOF > $test/$test.h
#ifndef ABSYSTEST${test}__H
#define ABSYSTEST${test}__H

#include "absys/test.h"

test test_$test(void);

#endif
EOF

cat << EOF > $test/$test.c
#include "absys/test.h"
#include "$test.h"

test test_$test(void) {
	return pass();
}
EOF
 
bash main.c.bash
bash main.c.bash > main.c
