#!/bin/sh
curDir=$(pwd)

if [[ $(command -v brew) == "" ]]; then
	echo "Installing Homebrew..."
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
	echo "Updating Homebrew..."
	brew update
fi

packages="gcc cmake"
packages+=" libssh"
#packages+=" libssh2"
packages+=" libnice"
packages+=" dylibbundler"

for pkg in $packages; do
    if brew list -1 | grep -q "^${pkg}\$"; then
        echo "Package '$pkg' is installed"
		brew reinstall $pkg
    else
        echo "Package '$pkg' is not installed"
		brew install $pkg
    fi
done

packages="microsoft-remote-desktop"

for pkg in $packages; do
    if brew list -1 | grep -q "^${pkg}\$"; then
        echo "Package '$pkg' is installed"
		brew reinstall --cask $pkg
    else
        echo "Package '$pkg' is not installed"
		brew install --cask $pkg
    fi
done

cd /usr/local/bin/
if [[ -f "gcc" ]]; then
    rm -rf gcc
fi
if [[ -f "g++" ]]; then
    rm -rf g++
fi
gVer=$(ls | grep "gcc-" | (head -n 1; grep ^/dev))
if [[ -f "$gVer" ]]; then
	ln -s "$gVer" gcc
fi
gVer=$(ls | grep "g++-" | (head -n 1; grep ^/dev))
if [[ -f "$gVer" ]]; then
	ln -s "$gVer" g++
fi
cd "$curDir"
