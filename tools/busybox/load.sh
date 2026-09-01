#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
CONFIG_DIR=$(realpath "${SRC_DIR}/../../configs/busybox/")
BUILD_DIR=$(realpath "$SRC_DIR/../../build/busybox/")

cp "${CONFIG_DIR}/defconfig" "${BUILD_DIR}/.config"

echo "Loaded config from ${CONFIG_DIR}/defconfig"
