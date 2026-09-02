#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)")

cd "${SRC_DIR}/x-tool/"
./load.sh
./build.sh

cd "${SRC_DIR/bootloader/"
./build.sh

cd "${SRC_DIR}/kernel/"
./load.sh
./build.sh
