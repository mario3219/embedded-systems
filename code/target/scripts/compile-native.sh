#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../")

cd ${SRC_DIR}
rm -rf build-native
mkdir build-native
cd build-native

../configure
make
