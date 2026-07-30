#!/bin/sh 

orig_dir=$(pwd)

if [ ! -d "~/crosstool-ng-1.28.0" ]; then
  wget -P ../sources http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.28.0.tar.xz
  tar -xvf ../sources/crosstool-ng-1.28.0.tar.xz
  cd ../sources/crosstool-ng-1.28.0
  ./bootstrap
  ./configure --enable-local
  make
  cd $orig_dir
fi

cd ../
cp configs/toolchain_config sources/crosstool-ng-1.28.0
cd sources/crosstool-ng-1.28.0
./ct-ng defconfig
./ct-ng build
cd $orig_dir
