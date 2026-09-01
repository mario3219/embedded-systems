#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR=$(realpath "${SRC_DIR}/../../sources/u-boot/")
COMPILER="aarch64-unknown-linux-gnu"
BOOT_TARGET="qemu_arm64_defconfig"

export PATH="$HOME/x-tools/${COMPILER}/bin:$PATH"
export CROSS_COMPILE="${COMPILER}-"

cd ${SOURCES_DIR}
make ${BOOT_TARGET}
make -j"$(nproc)"

ls -lh u-boot u-boot.bin
file u-boot
file u-boot.bin
