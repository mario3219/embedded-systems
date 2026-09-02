#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
BUILD_DIR=$(realpath -m "${SRC_DIR}/build/linux")
LINUX_DIR=$(realpath "${SRC_DIR}/sources/linux/")
CONFIG_DIR=$(realpath "${SRC_DIR}/configs/kernel/")

cp "${CONFIG_DIR}/defconfig" "${BUILD_DIR}/.config"
cd ${LINUX_DIR}
make O=${BUILD_DIR} ARCH=arm64 olddefconfig
