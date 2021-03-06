#!/bin/sh
BASEDIR=$(dirname "$0")
cd $BASEDIR

curDir=$(pwd)

rm -rf ./plibsys
rm -rf ./macosx
git clone https://github.com/saprykin/plibsys.git
mkdir ./macosx
cd ./macosx
cmake -DCMAKE_BUILD_TYPE=Release ../plibsys
make
cd ..
prefix="./plibsys/src"
prefixx="./plibsys/src/"
echo "" > "$prefixx"plibsysconfig.h
for file in "`find "$prefix" -name "p*.h"`"
do {
	file=${file//$prefixx/}
	for f in $file
	do {
		echo "$f"
		#find "$prefix" -type f -exec sed -i "s+#include <perror.h>+#include \"perror.h\"+g" {} +
		find "$prefix" -type f -exec sed -i '' "s+#include <$f>+#include \"$f\"+g" {} +
	} done
} done

cd "$curDir"