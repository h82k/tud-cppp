#!/bin/bash

for file in $(find day{1,2,3,4} -name "Makefile");
do
  echo "---"
  echo "----------- $file ----------"
  echo "---"
  make -C $(dirname $file)
done
