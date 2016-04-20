#!/bin/bash

while read input
do
	if [ "${input:0:3}" == "***" ]
	then
		line=$(echo "$input" | grep -oP '\(\K[^\)]+' | head -n1);
		file=$(echo "$input" | grep -oP '\w*\.[ch]' | head -n1);
		errmsg=$(echo "$input" | grep -oP ':.*' | head -n1);
		echo $file:$line:0: error$errmsg;
		err=1;
	fi
done

if [ "$err" = "1" ]
then
	exit 1;
else
	exit 0;
fi
