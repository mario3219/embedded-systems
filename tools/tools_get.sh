#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR="${SRC_DIR}/../sources/"

mkdir -p $SOURCES_DIR

if [ ! -d "$SOURCES_DIR/crosstool-ng-1.28.0" ]; then
  cd "x-tool/"
  ./get.sh
  cd ${SRC_DIR}
fi

if [ ! -d "${SOURCES_DIR}/u-boot/.git" ]; then
  cd "bootloader"
  ./get.sh
  cd ${SRC_DIR}
fi

if [ ! -d "${SOURCES_DIR}/linux/.git" ]; then
  cd "kernel"
  ./get.sh
  cd ${SRC_DIR}
fi

if [ ! -d "${SOURCES_DIR}/busybox/.git" ]; then
  cd "busybox"
  ./get.sh
  cd ${SRC_DIR}
fi
