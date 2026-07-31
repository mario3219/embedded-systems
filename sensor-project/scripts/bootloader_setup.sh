#!/bin/bash

# DIRECTORIES
SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

# TOOLCHAIN
TOOLCHAIN="arm-unknown-linux-gnueabihf"

export PATH="$SRC_DIR/sources/toolchain/$TOOLCHAIN/bin:$PATH"
export CROSS_COMPILE=$TOOLCHAIN

cd $SRC_DIR

if [ ! -d "u-boot/.git" ]; then
  cd $SRC_DIR/sources/
  git clone https://git.u-boot-project.org/u-boot/u-boot.git
  cd $SRC_DIR
fi

cp configs/uboot_defconfig sources/u-boot/configs/
cd sources/u-boot/
make uboot_defconfig
make -j"$(nproc)"
