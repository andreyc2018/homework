#!/bin/sh
sed 's/^\(.*\)\t.*\t.*/\1/' ip_filter.tsv | sort -r -n -t . -k 1,1 -k 2,2 -k 3,3 -k 4,4 > ip_filter.result.sorted
sort -r -n -t . -k 1,1 -k 2,2 -k 3,3 -k 4,4 ip_filter.result.sorted > ip_filter.result
grep "^\<1\>\." ip_filter.result.sorted >> ip_filter.result
grep "^\<46\>\.\<70\>" ip_filter.result.sorted  >> ip_filter.result
grep "\<46\>" ip_filter.result.sorted >> ip_filter.result

