#!/bin/bash

for testcase in $2/*.in
do
    echo -n "TEST ${testcase%.in}: "
    if diff "${testcase%in}out" <($1 < $testcase) > /dev/null
    then
        echo "OK"
    else
        echo "ERROR"
    fi
done