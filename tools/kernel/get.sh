#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
SOURCES_DIR=$(realpath "${SRC_DIR}/sources/")
BUILD_DIR=$(realpath -m "${SRC_DIR}/build/linux")
LINUX_DIR=$(realpath "${SRC_DIR}/sources/linux/")
COMPILER="aarch64-unknown-linux-gnu"

REPO_LINK="https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git"

export PATH="$HOME/x-tools/${COMPILER}/bin:$PATH"

cd "${SOURCES_DIR}"
if [ ! -d "${SOURCES_DIR}/linux/.git" ]; then
  git clone ${REPO_LINK}
  cd ${LINUX_DIR}
  git checkout v7.1
fi

mkdir -p ${BUILD_DIR}
cd ${LINUX_DIR}
make ARCH=arm64 mrproper
make \
    O="${BUILD_DIR}" \
    ARCH=arm64 \
    CROSS_COMPILE="${COMPILER}-" \
    defconfig
