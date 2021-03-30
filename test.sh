#!/bin/bash

tmp_dir=$(mktemp -d -t ipp_testXXXXXX)

for testcase in $2/*.in
do
    echo ""
    echo "TEST ${testcase%.in}: "
    cat $testcase | $1 1> $tmp_dir/test.out 2> $tmp_dir/test.err


    if diff "${testcase%in}out" $tmp_dir/test.out > /dev/null
    then
        echo -n "out: OK      "
    else
        echo -n "out: ERROR   "
    fi

    if diff "${testcase%in}err" $tmp_dir/test.err > /dev/null
    then 
        echo " err: OK"
    else
        echo " err: ERROR"
    fi
done

rm -rf $tmp_dir