#!/bin/sh 

orig_dir=$(pwd)

cd ../sources

if [ ! -d "u-boot/.git" ]; then
  git clone https://git.u-boot-project.org/u-boot/u-boot.git
fi

cd ../
cp configs/uboot_defconfig sources/u-boot/
cd sources/u-boot/
make uboot_defconfig

export PATH="$src_dir/sources/toolchain/arm-unknown-linux-gnueabihf/bin:$PATH"
export CROSS_COMPILE=arm-unknown-linux-gnueabihf-

make -j"$(nproc)"
