#!/bin/bash

export EXERCISES_ROOT=$(cd $(dirname $0); pwd)
echo $EXERCISES_ROOT
solutionsDirectory=$EXERCISES_ROOT/solutions
templatesDirectory=$EXERCISES_ROOT/templates

which clang++ > /dev/null 2> /dev/null |true
if [ $? -ne 0 ];
then
  echo "Missing clang++ compiler!"
  exit -1
fi

for file in \
  $(find ${solutionsDirectory}/day{1,2,3,4} -name "Makefile") \
  $(find ${solutionsDirectory}/day5/*_C_* -name "Makefile") \
  $(find ${solutionsDirectory}/elevator -name "Makefile") \
  $(find ${templatesDirectory}/day{5} -name "Makefile");
do
  echo "---"
  echo "----------- $file ----------"
  echo "---"
  make -C $(dirname $file) $@
done
