#!/bin/bash
curDir=$(pwd)

packages="base-devel gcc mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake git"
packages+=" mingw-w64-x86_64-libssh"
#packages+=" mingw-w64-x86_64-libssh2"
packages+=" mingw-w64-x86_64-libnice"
packages+=" mingw-w64-x86_64-curl"
packages+=" mingw-w64-x86_64-rocksdb"
pacman -Syu --noconfirm
pacman -S --needed --noconfirm $packages
pacman -Scc --noconfirm

cd "$curDir"
