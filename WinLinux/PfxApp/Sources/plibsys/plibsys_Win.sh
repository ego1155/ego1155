#!/bin/bash
curDir=$(pwd)

rm -rf ./plibsys
rm -rf ./win
git clone https://github.com/saprykin/plibsys.git
mkdir ./win
cd ./win
cmake -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Release ../plibsys
make

cd "$curDir"
