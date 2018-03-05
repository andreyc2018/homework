#!/bin/sh

test_file="$1"

if [ ! -r "$test_file" ]
then
    echo "error in args: \"$test_file\""
    exit 1
fi

for line in `cat $test_file`
do
    echo $line 1>&2
    echo $line
    sleep 1
done

