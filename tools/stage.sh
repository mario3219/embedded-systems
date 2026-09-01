#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../")
ROOTFS_DIR=$(realpath -m "${SRC_DIR}/rootfs/")

mkdir -p "${ROOTFS_DIR}/images"
cd "${ROOTFS_DIR}/staging"

find . -print0 \
    | cpio --null -ov --format=newc \
    | gzip -9 > ../images/rootfs.cpio.gz

ls -lh ${ROOTFS_DIR}/images/rootfs.cpio.gz
