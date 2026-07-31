#!/bin/bash

# PATHS
SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")
TOOLCHAIN="arm-unknown-linux-gnueabihf"
SYSROOT="$SRC_DIR/sources/toolchain/$TOOLCHAIN/$TOOLCHAIN/sysroot"
STAGING_TARGET="$SRC_DIR/rootfs/staging/lib/"

export PATH="$SRC_DIR/sources/toolchain/$TOOLCHAIN/bin:$PATH"

cp -a "$SYSROOT/lib/ld-2.28.so" "$STAGING_TARGET"
cp -a "$SYSROOT/lib/libc-2.28.so" "$STAGING_TARGET"

cd $SRC_DIR
cp scripts/init rootfs/staging/
chmod u+x rootfs/staging/init
mkdir -p rootfs/images
cd rootfs/staging
find . -print0 \
    | cpio --null -ov --format=newc \
    | gzip -9 > ../images/rootfs.cpio.gz
