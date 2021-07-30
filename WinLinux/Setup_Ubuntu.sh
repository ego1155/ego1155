#!/bin/sh
curDir=$(pwd)

apt-get update -y && apt-get upgrade -y && apt-get autoremove -y && apt-get clean -y

packages="build-essential gcc-multilib cmake git"
packages=$packages+" libssh-dev"
#packages=$packages+" git autoconf libtool libssl-dev freerdp2-x11"
#packages=$packages+" libssh2-1-dev"
packages=$packages+" libglib2.0-dev libnice-dev"

apt-get install $packages -y

#git clone https://github.com/libssh2/libssh2.git
#cd libssh2
#autoreconf -fi
#./configure --with-openssl CPPFLAGS="-I/usr/include/openssl" LDFLAGS="-L/usr/lib/x86_64-linux-gnu"
#sudo make install
#sudo ldconfig
#cd "$curDir"
#rm -rf libssh2

#wget https://ftpmirror.gnu.org/libmicrohttpd/libmicrohttpd-latest.tar.gz
#tar xvf libmicrohttpd-latest.tar.gz
#cd libmicrohttpd*
#./configure --disable-messages --disable-postprocessor --disable-dauth
#./configure
#make
#sudo make install # installation puts .h files in /usr/local/include and library in /usr/local/lib
#sudo ldconfig # just in case... it doesn't hurt :)
#cd "$curDir"
#rm -rf libmicrohttpd-latest.tar.gz
#rm -rf libmicrohttpd*

cd "$curDir"
