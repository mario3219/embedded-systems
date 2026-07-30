#!/bin/sh 

orig_dir=$(pwd)

wget -P ~/ http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.28.0.tar.xz
tar -xvf ~/crosstool-ng-1.28.0.tar.xz
cd ~/crosstool-ng-1.28.0
./bootstrap
./configure --enable-local
make
cd $orig_dir
