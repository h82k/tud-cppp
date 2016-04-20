#!/bin/bash

read input;

if [ "${input:0:3}" == "***" ]
then
	line=$(echo "$input" | grep -oP '\(\K[^\)]+' | head -n1);
	file=$(echo "$input" | grep -oP '\w*\.[ch]' | head -n1);
	errmsg=$(echo "$input" | grep -oP ':.*' | head -n1);
	echo $file:$line:0: error$errmsg;
	exit 1;
fi

exit;
