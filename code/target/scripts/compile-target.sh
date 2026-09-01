#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../")
TARGET="${HOME}/x-tools/aarch64-unknown-linux-gnu/bin/aarch64-unknown-linux-gnu"
TARGET_TRIPLET="aarch64-unknown-linux-gnu"

cd ${SRC_DIR}
rm -rf build-target
mkdir build-target
cd build-target

export TARGET
../configure \
    --build="$(gcc -dumpmachine)" \
    --host="$TARGET_TRIPLET" \
    CC="$TARGET-gcc" \
    AR="$TARGET-ar" \
    RANLIB="$TARGET-ranlib" \
    STRIP="$TARGET-strip"

make V=1
file app
