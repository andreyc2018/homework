#!/bin/sh

task="$1"
input="$2"
output="$3"

cat $input | $task > result
diff $output result >/dev/null && echo "Ok" || echo "Fail"

