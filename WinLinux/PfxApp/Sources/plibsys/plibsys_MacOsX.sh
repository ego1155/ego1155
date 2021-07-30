#!/bin/sh
curDir=$(pwd)

rm -rf ./plibsys
rm -rf ./macosx
git clone https://github.com/saprykin/plibsys.git
mkdir ./macosx
cd ./macosx
cmake -DCMAKE_BUILD_TYPE=Release ../plibsys
make

cd "$curDir"
