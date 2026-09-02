#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
SOURCES_DIR=$(realpath "${SRC_DIR}/sources/linux/")
BUILD_DIR=$(realpath -m "${SRC_DIR}/build/linux")

cd "${SOURCES_DIR}"
make O="${BUILD_DIR}" ARCH=arm64 menuconfig
