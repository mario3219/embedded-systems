#!/bin/bash

# DIRECTORIES
SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

# TOOLCHAIN
TOOLCHAIN="arm-unknown-linux-gnueabihf"

export PATH="$SRC_DIR/sources/toolchain/$TOOLCHAIN/bin:$PATH"

cd $SRC_DIR/sources/

if [ ! -d "busybox/.git" ]; then
  git clone https://git.busybox.net/busybox
fi

cd busybox
mkdir -p ../../build/busybox
make O=../../build/busybox defconfig

cp $SRC_DIR/configs/busybox_defconfig $SRC_DIR/build/busybox/.config

make \
    O=../../build/busybox \
    ARCH=arm \
    CROSS_COMPILE=$TOOLCHAIN- \
    -j"$(nproc)"

mkdir -p $SRC_DIR/rootfs/staging

make \
    O=../../build/busybox \
    ARCH=arm \
    CROSS_COMPILE=$TOOLCHAIN- \
    CONFIG_PREFIX="$(realpath ../../rootfs/staging)" \
    install

cd $SRC_DIR

mkdir -p \
    rootfs/staging/dev \
    rootfs/staging/proc \
    rootfs/staging/sys \
    rootfs/staging/etc \
    rootfs/staging/tmp \
    rootfs/staging/run \
    rootfs/staging/mnt \
    rootfs/staging/root

chmod 1777 rootfs/staging/tmp
