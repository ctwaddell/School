#!/bin/bash

TESTS_PATH="/p/course/cs537-yuvraj/tests/p2A/tests"

for testdesc in $( ls "$TESTS_PATH/" -v | grep ".desc" ); do
    # echo -n $testdesc
    echo -n "  $testdesc - "
    echo $(head -1 $TESTS_PATH/$testdesc)
done
