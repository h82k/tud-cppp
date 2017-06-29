#/bin/bash
#
# Script for converting the line ending of a single file from CRLF to LF
# Author: Roland Kluge
# Date:   2017-04-10
#

if [ "$1" == "" ]
then
  echo "Expect file to be converted as first parameter to script."
  exit
fi 

if [ ! -f "$1" ]
then
  echo "No such file: '$1'"
  exit
fi

echo "Converting '$1'"
sed -i "s/^M$//" $1
