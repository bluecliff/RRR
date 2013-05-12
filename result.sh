#!/bin/sh
echo -e "n\ttime\tsize\n" > result.txt
for i in {10..27}
	do
		echo $i
		./test_rrr $i >> result.txt
	done
