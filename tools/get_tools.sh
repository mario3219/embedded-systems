#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR="${SRC_DIR}/../sources/"

mkdir -p $SOURCES_DIR

if [ ! -d "$SOURCES_DIR/crosstool-ng-1.28.0" ]; then
  cd "x-tool/"
  ./crosstool_get.sh
fi

if [ ! -d "${SOURCES_DIR}/u-boot/.git" ]; then
  cd "bootloader"
  ./bootloader_get.sh
fi

if [ ! -d "${SOURCES_DIR}/linux/.git" ]; then
  cd "kernel"
  ./kernel_get.sh
fi
