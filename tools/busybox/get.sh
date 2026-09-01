#!/bin/bash
set -e

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
SOURCES_DIR=$(realpath "${SRC_DIR}/sources/")
NCURSES_PATCH=$(realpath "${SRC_DIR}/configs/busybox/busybox-1.36.1-fix-unable-to-find-ncurses.patch")
CONFIG_PATH=$(realpath "${SRC_DIR}/configs/busybox/defconfig")
BUILD_DIR=$(realpath -m "${SRC_DIR}/build/busybox")

REPO_LINK="https://git.busybox.net/busybox"

if [ ! -d "${SOURCES_DIR}/busybox/.git" ]; then
  cd "${SOURCES_DIR}"
  git clone ${REPO_LINK}
fi

cd "${SOURCES_DIR}/busybox/"
git checkout 1_37_0
git reset --hard 1_37_0

patch -p1 < "${NCURSES_PATCH}"

mkdir -p ${BUILD_DIR}
make O=${BUILD_DIR} defconfig
cp ${CONFIG_PATH} ${BUILD_DIR}/.config

echo "Copied config to ${BUILD_DIR}/.config"
echo "Patched with ${NCURSES_PATCH}"
