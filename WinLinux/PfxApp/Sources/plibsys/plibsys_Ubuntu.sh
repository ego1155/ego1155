#!/bin/sh
curDir=$(pwd)

rm -rf ./plibsys
rm -rf ./ubuntu
git clone https://github.com/saprykin/plibsys.git
mkdir ./ubuntu
cd ./ubuntu
cmake -DCMAKE_BUILD_TYPE=Release ../plibsys
make

cd "$curDir"
