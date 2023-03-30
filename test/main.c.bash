testroot="."
tests="$(find $testroot -mindepth 1 -maxdepth 1 -type d -exec basename {} \; | xargs echo)"

echo "#include \"absys/test.h\""
for test in $tests; do
	echo "#include \"$test/$test.h\""
done

cat << EOF

int main(int argc, char * argv[]) {
EOF

for test in $tests; do
    echo "	suite $test = test_suite(NULL, \"$test\");"
    echo "	test_case($test, \"$test\", test_$test);"
done

cat << EOF
	return test_run(argc, argv);
}
EOF

