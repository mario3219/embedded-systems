#!/bin/bash
set -e

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR=$(realpath "${SRC_DIR}/../../sources/")
NCURSES_PATCH=$(realpath "${SOURCES_DIR}/../configs/busybox/busybox-1.36.1-fix-unable-to-find-ncurses.patch")
ACCEL_PATCH=$(realpath "${SOURCES_DIR}/../configs/busybox/busybox-1.37.0-fix-sha1-hwaccel-aarch64.patch")

REPO_LINK="https://git.busybox.net/busybox"

if [ ! -d "${SOURCES_DIR}/busybox/.git" ]; then
  cd "${SOURCES_DIR}"
  git clone ${REPO_LINK}
fi

cd "${SOURCES_DIR}/busybox/"
git checkout 1_37_0
git reset --hard 1_37_0

patch -p1 < "${NCURSES_PATCH}"
patch -p1 < "${ACCEL_PATCH}"

mkdir -p ../../build/busybox
make O=../../build/busybox defconfig

echo "Patched with ${NCURSES_PATCH}"
echo "Patched with ${ACCEL_PATCH}"
