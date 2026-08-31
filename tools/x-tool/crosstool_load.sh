#!/bin/bash

SRC_DIR=$(realpath "$(pwd)/")
CROSS_DIR=$(realpath "${SRC_DIR}/../../sources/crosstool-ng-1.28.0/")
CONFIG=$(realpath "${SRC_DIR}/../../configs/x-tool/")

cp "${CONFIG}/defconfig" "${CROSS_DIR}"
cd ${CROSS_DIR}
./ct-ng olddefconfig

echo "Loaded to ${CROSS_DIR}"
