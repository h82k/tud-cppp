#!/bin/bash

solutionsDirectory=$(dirname $0)
for file in $(find ${solutionsDirectory}/day{1,2,3,4} -name "Makefile");
do
  echo "---"
  echo "----------- $file ----------"
  echo "---"
  make -C $(dirname $file)
done
