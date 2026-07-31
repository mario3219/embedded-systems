#!/bin/bash

# DIRECTORIES
SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

# TOOLCHAIN
TOOLCHAIN="arm-unknown-linux-gnueabihf"

# LINUX REPO
REPO="https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git"

# EXPORT VARIABLES
export PATH="$SRC_DIR/sources/toolchain/$TOOLCHAIN/bin:$PATH"

cd $SRC_DIR

if [ ! -d "$SRC_DIR/sources/linux/.git" ]; then
  cd sources
  git clone $REPO
  git checkout v7.1
  cd $SRC_DIR
fi

cd sources/linux
mkdir -p $SRC_DIR/build/linux
cp $SRC_DIR/configs/linux_defconfig $SRC_DIR/sources/linux/arch/arm/configs/custom_qemu_arm_defconfig
make O=../../build/linux ARCH=arm custom_qemu_arm_defconfig

make \
    O=../../build/linux \
    ARCH=arm \
    CROSS_COMPILE=$TOOLCHAIN- \
    -j"$(nproc)"
