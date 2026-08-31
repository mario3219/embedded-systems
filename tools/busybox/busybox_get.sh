#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR=$(realpath "${SRC_DIR}/../../sources/")

REPO_LINK="https://git.busybox.net/busybox"

if [ ! -d "${SOURCES_DIR}/busybox/.git" ]; then
  cd "${SOURCES_DIR}"
  git clone ${REPO_LINK}
fi

cd "${SOURCES_DIR}/busybox/"
git checkout 1_37_0
mkdir -p ../../build/busybox
make O=../../build/busybox defconfig
