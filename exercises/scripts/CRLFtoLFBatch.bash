#/bin/bash
#
# Script for batch converting the line ending of files from CRLF to LF
# Author: Roland Kluge
# Date:   2017-04-10
#

pattern="*.h"
root=".."
workingDir=$(dirname $0)
find $root -name $pattern -exec sh "$workingDir/CRLFtoLFSingle.bash" {} \;
