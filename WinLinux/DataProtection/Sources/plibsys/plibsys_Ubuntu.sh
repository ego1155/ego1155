#!/bin/bash
BASEDIR=$(dirname "$0")
cd $BASEDIR

curDir=$(pwd)

rm -rf ./plibsys
rm -rf ./ubuntu
git clone https://github.com/saprykin/plibsys.git
mkdir ./ubuntu
cd ./ubuntu
cmake -DCMAKE_BUILD_TYPE=Release ../plibsys
make
cd ..
prefix="./plibsys/src/"
echo "" > "$prefix"plibsysconfig.h
for file in "`find "$prefix" -name "p*.h"`"
do {
	file=${file//$prefix/}
	for f in $file
	do {
		echo "$f"
		#find "$prefix" -type f -exec sed -i "s+#include <perror.h>+#include \"perror.h\"+g" {} +
		find "$prefix" -type f -exec sed -i "s+#include <$f>+#include \"$f\"+g" {} +
	} done
} done

cd "$curDir"
