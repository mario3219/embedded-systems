#!/bin/sh 

orig_dir=$(pwd)
cd ../sources/crosstool-ng-1.28.0
./ct-ng savedefconfig
cp defconfig ../../configs/toolchain_config
cd $orig_dir
