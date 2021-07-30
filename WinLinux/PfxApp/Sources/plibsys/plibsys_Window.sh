#!/bin/bash
curDir=$(pwd)

rm -rf ./plibsys
rm -rf ./window
git clone https://github.com/saprykin/plibsys.git
mkdir ./window
cd ./window
cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release ../plibsys
make

cd "$curDir"
