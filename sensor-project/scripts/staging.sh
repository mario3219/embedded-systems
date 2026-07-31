#!/bin/bash

# DIRECTORIES
SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

cd $SRC_DIR
cp scripts/init rootfs/staging/
chmod u+x rootfs/staging/init
mkdir -p rootfs/images
cd rootfs/staging
find . -print0 \
    | cpio --null -ov --format=newc \
    | gzip -9 > ../images/rootfs.cpio.gz
