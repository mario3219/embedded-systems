#!/bin/sh 

orig_dir=$(pwd)
cd ../../sources/
git clone https://git.busybox.net/busybox
cd busybox
mkdir -p ../../build/busybox
make O=../../build/busybox defconfig
cd $orig_dir
