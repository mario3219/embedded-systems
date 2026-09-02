#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")

cd "${SOURCES_DIR}/x-tool/"
./load.sh
./build.sh

cd "${SOURCES_DIR}/bootloader/"
./build.sh

cd "${SOURCES_DIR}/kernel/"
./build.sh
