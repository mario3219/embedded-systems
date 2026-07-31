#!/bin/sh 

orig_dir=$(pwd)
src_dir=$orig_dir/../
export src_dir

if [ ! -d "../sources/crosstool-ng-1.28.0" ]; then
  wget -P ../sources http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.28.0.tar.xz
  tar -xvf ../sources/crosstool-ng-1.28.0.tar.xz -C ../sources/
  cd ../sources/crosstool-ng-1.28.0
  ./bootstrap
  ./configure --enable-local
  make
  cd $orig_dir
fi

cd ../
mkdir -p sources/toolchain
cp configs/toolchain_config sources/crosstool-ng-1.28.0/.config
cd sources/crosstool-ng-1.28.0
./ct-ng olddefconfig
./ct-ng build
cd $orig_dir
