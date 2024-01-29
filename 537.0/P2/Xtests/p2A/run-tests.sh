#!/bin/bash
set -e
TEST_DIR=/p/course/cs537-yuvraj/tests/p2A
TMP_DIR=537_su22_test_tmp
clean_up () {
    ARG=$?
    
    if [ ! $ARG -eq 0 ]; then
        echo "*** clean_up"
    fi

    if [ -d $TMP_DIR ]; then
        rm -rf $TMP_DIR
    fi

    if [ -d "tester" ]; then
        rm -rf tester/
    fi
    exit $ARG
} 
trap clean_up EXIT

if [ -d $TMP_DIR ]; then
    rm -rf $TMP_DIR
fi

mkdir $TMP_DIR
cp -r src $TMP_DIR
cp -r $TEST_DIR/tests $TMP_DIR/
cp $TEST_DIR/test-getnumsyscalls.sh $TMP_DIR/
cp -r $TEST_DIR/tester .
chmod +x tester/run-tests.sh
chmod +x tester/run-xv6-command.exp
chmod +x tester/xv6-edit-makefile.sh
chmod +x $TMP_DIR/src/sign.pl

cd $TMP_DIR
chmod +x test-getnumsyscalls.sh
./test-getnumsyscalls.sh $*
cd ../

cp -r $TMP_DIR/tests/ .
cp -r $TMP_DIR/tests-out .

rm -rf $TMP_DIR
rm -rf tester/
