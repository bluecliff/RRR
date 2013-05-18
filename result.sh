#!/bin/sh
echo -e "m\tn\tsize\tbitpersym\tptimeofget\tptimeofrank\n" > result.txt
for i in {20..28}
	do
		echo $i
		./test_rrr $i >> result.txt
	done
