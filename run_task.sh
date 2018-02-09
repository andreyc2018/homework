#!/bin/sh

task="`readlink -f $1`"
input="`readlink -f $2`"
output="`readlink -f $3`"

cat $input | $task > result
diff $output result >/dev/null && echo "Ok" || echo "Fail"
