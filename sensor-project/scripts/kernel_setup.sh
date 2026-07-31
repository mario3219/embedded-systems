#!/bin/sh 

orig_dir=$(pwd)
src_dir=$orig_dir/../
cd $src_dir/sources/

if [ ! -d "linux/.git" ]; then
  git clone https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
  git checkout v7.1
fi

cd $src_dir
mkdir -p build/linux
cp configs/linux_config sources/linux/arch/arm/configs/custom_qemu_arm_defconfig
make O=../../build/linux ARCH=arm custom_qemu_arm_defconfig

cd sources/linux
export PATH="$src_dir/sources/toolchain/arm-unknown-linux-gnueabihf/bin:$PATH"
make \
    O=../../build/linux \
    ARCH=arm \
    CROSS_COMPILE=arm-unknown-linux-gnueabihf- \
    -j"$(nproc)"
