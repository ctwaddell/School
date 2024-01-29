#!/bin/bash

TESTS_PATH="/p/course/cs537-yuvraj/tests/p2B"

if [ "$TESTS_PATH" != $(pwd) ]; then
    rm -rf ./tests
    rm -rf ./tester
fi

rm -rf ./tests-out

cp -r $TESTS_PATH/tests ./tests
cp -r $TESTS_PATH/tester ./tester

chmod +x ./tester/run-tests.sh

utility="mysh"

echo
echo "*** Start testing $utility..."

echo
echo "*** Compiler output for $utility"
rm -f ./mysh
make

if [ ! -f $utility ]; then
    echo "*** ERROR: $utility not built by make command"
    exit
fi

echo
echo "*** Testing output for $utility"
./tester/run-tests.sh -c

#echo
#echo "*** Linting output for $utility"
#python /p/course/cs537-yuvraj/public/cpplint.py --root=/p/course/cs537-yuvraj/turnin --extensions=c,h $utility.c

echo
echo "*** Valgrind output for $utility"
valgrind --show-reachable=yes ./$utility tests/9.in > /dev/null
valgrind --show-reachable=yes ./$utility tests/22.in > /dev/null
