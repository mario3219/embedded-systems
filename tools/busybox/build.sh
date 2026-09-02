#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
BUSYBOX_DIR=$(realpath "${SRC_DIR}/sources/busybox/")
BUILD_DIR=$(realpath "$SRC_DIR/build/busybox/")
STAGING_DIR=$(realpath -m "${SRC_DIR}/rootfs/staging/")
INIT_PATH=$(realpath "${SRC_DIR}/configs/busybox/init")
COMPILER="aarch64-unknown-linux-gnu"

export PATH="$HOME/x-tools/${COMPILER}/bin:$PATH"

rm -rf "${SRC_DIR}/rootfs"
mkdir -p "${STAGING_DIR}"

cd ${BUSYBOX_DIR}

make \
    O=${BUILD_DIR} \
    ARCH=arm \
    CROSS_COMPILE=${COMPILER}- \
    -j"$(nproc)"

make \
    O=${BUILD_DIR} \
    ARCH=arm \
    CROSS_COMPILE=${COMPILER}- \
    CONFIG_PREFIX=${STAGING_DIR} \
    install

mkdir -p \
    ${STAGING_DIR}/dev \
    ${STAGING_DIR}/proc\
    ${STAGING_DIR}/sys \
    ${STAGING_DIR}/etc \
    ${STAGING_DIR}/tmp \
    ${STAGING_DIR}/run \
    ${STAGING_DIR}/mnt \
    ${STAGING_DIR}/root \
    ${SRC_DIR}/data/qemu-output

chmod 1777 ${STAGING_DIR}/tmp
cp "${INIT_PATH}" "${STAGING_DIR}"

file ${STAGING_DIR}/bin/busybox
file ${BUILD_DIR}/busybox
ls -l ${STAGING_DIR}/init
ls -l ${STAGING_DIR}/bin/sh
