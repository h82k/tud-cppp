#/bin/bash
#
# Script for batch converting the line ending of files from CRLF to LF
# Author: Roland Kluge
# Date:   2017-04-10
#

root="../.."
workingDir=$(dirname $0)
find . \( -name "*.h" -or -name "*.c" -or -name "*.cpp" -or -name "*.tex" \) -exec sh "$workingDir/CRLFtoLFSingle.bash" {} \;
