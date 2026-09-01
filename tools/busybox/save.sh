#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
CONFIG_DIR=$(realpath "${SRC_DIR}/../../configs/busybox/")
BUILD_DIR=$(realpath "$SRC_DIR/../../build/busybox/")

cp "${BUILD_DIR}/.config" "${CONFIG_DIR}/defconfig"

echo "Saved config to ${CONFIG_DIR}/defconfig"
