#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
ROOTFS_DIR=$(realpath -m "${SRC_DIR}/rootfs/")
BUILD_DIR=$(realpath -m "${SRC_DIR}/code/target/build-target/")

if [ ! -d "${BUILD_DIR}" ]; then
  echo "Target is not compiled"
  exit
fi

cd ${BUILD_DIR}
make DESTDIR="$(realpath ${ROOTFS_DIR}/staging)" install
