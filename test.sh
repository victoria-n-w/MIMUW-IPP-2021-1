#!/bin/bash

tmp_dir=$(mktemp -d -t ipp_testXXXXXX)

for testcase in $2/*.in
do
    echo ""
    echo "TEST ${testcase%.in}: "
    $1 <$testcase 1> $tmp_dir/test.out 2> $tmp_dir/test.err

    echo -n "exit code: $?     "


    if diff "${testcase%in}out" $tmp_dir/test.out > /dev/null
    then
        echo -n "out: OK      "
    else
        echo -n "out: ERROR   "
    fi

    if diff "${testcase%in}err" $tmp_dir/test.err > /dev/null
    then 
        echo -n " err: OK"
    else
        echo -n " err: ERROR"
    fi

    valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all $1 < $testcase > /dev/null 2>/dev/null
    retVal=$?

    if [[ "$retVal" -eq 123 ]];
    then
        echo "    memory: ERROR"
    else
        echo "    memory: OK"
    fi

done

rm -rf $tmp_dir