#!/bin/bash

SRC_DIR=$(realpath "$(pwd)/")
CROSS_DIR=$(realpath "${SRC_DIR}/../../sources/crosstool-ng-1.28.0/")
CONFIG=$(realpath "${SRC_DIR}/../../configs/x-tool/")

cd "${CROSS_DIR}"
./ct-ng savedefconfig
cp "${CROSS_DIR}/defconfig" "${CONFIG}"

echo "Saved ${CONFIG}/defconfig"
