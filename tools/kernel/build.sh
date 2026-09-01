#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
SOURCES_DIR=$(realpath "${SRC_DIR}/sources/linux/")
BUILD_DIR=$(realpath -m "${SRC_DIR}/build/linux")
COMPILER="aarch64-unknown-linux-gnu"

export PATH="$HOME/x-tools/${COMPILER}/bin:$PATH"

mkdir -p ${BUILD_DIR}
cd "${SOURCES_DIR}"
make ARCH=arm64 mrproper

make \
    O="${BUILD_DIR}" \
    ARCH=arm64 \
    CROSS_COMPILE="${COMPILER}-" \
    defconfig

yes "" | make \
    O=${BUILD_DIR} \
    ARCH=arm64 \
    CROSS_COMPILE=${COMPILER}- \
    -j"$(nproc)"

ls -lh ${BUILD_DIR}/arch/arm64/boot/Image
ls -lh ${BUILD_DIR}/vmlinux
find ${BUILD_DIR}/arch/arm64/boot/dts -name '*.dtb' | head -20
