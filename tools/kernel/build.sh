#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
SOURCES_DIR=$(realpath "${SRC_DIR}/sources/linux/")
BUILD_DIR=$(realpath -m "${SRC_DIR}/build/linux")
COMPILER="aarch64-unknown-linux-gnu"

export PATH="$HOME/x-tools/${COMPILER}/bin:$PATH"

cd "${SOURCES_DIR}"

yes "" | make \
    O=${BUILD_DIR} \
    ARCH=arm64 \
    CROSS_COMPILE=${COMPILER}- \
    -j"$(nproc)"

ls -lh ${BUILD_DIR}/arch/arm64/boot/Image
ls -lh ${BUILD_DIR}/vmlinux
find ${BUILD_DIR}/arch/arm64/boot/dts -name '*.dtb' | head -20
