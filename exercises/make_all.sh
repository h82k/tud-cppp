#!/bin/bash

export EXERCISES_ROOT=$(cd $(dirname $0); pwd)
echo $EXERCISES_ROOT
latexDirectory=$EXERCISES_ROOT/latex
solutionsDirectory=$EXERCISES_ROOT/solutions
templatesDirectory=$EXERCISES_ROOT/templates

for file in \
  $(find ${latexDirectory} -name "Makefile") \
  $(find ${solutionsDirectory}/{01,02,03,04,06}* -name "Makefile") \
  $(find ${solutionsDirectory}/05_c/*_C_* -name "Makefile") \
  $(find ${templatesDirectory}/05 -name "Makefile");
do
  echo "---"
  echo "----------- $file ----------"
  echo "---"
  make -C $(dirname $file) $@
done
