lcov --base-directory ./test --directory ./test --capture --output-file testcov.info
genhtml -o ./doc/testcov testcov.info
