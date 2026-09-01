#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR=$(realpath "${SRC_DIR}/../../sources/")
PATCH_PATH=$(realpath "${SOURCES_DIR}/../configs/busybox/busybox-1.36.1-fix-unable-to-find-ncurses.patch")

REPO_LINK="https://git.busybox.net/busybox"

if [ ! -d "${SOURCES_DIR}/busybox/.git" ]; then
  cd "${SOURCES_DIR}"
  git clone ${REPO_LINK}
fi

cd "${SOURCES_DIR}/busybox/"
git checkout 1_37_0
git reset --hard 1_37_0
patch -p1 < ${PATCH_PATH}
mkdir -p ../../build/busybox
make O=../../build/busybox defconfig
