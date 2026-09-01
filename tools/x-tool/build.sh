#!/bin/bash

SRC_DIR=$(realpath "$(pwd)/")
CROSS_DIR=$(realpath "${SRC_DIR}/../../sources/crosstool-ng-1.28.0/")
BUILD_DIR=$(realpath "${CROSS_DIR}/../")

cd ${CROSS_DIR}

export BUILD_DIR
export PATH=/usr/bin:/bin
unset PYTHON
unset PYTHONHOME
unset PYTHONPATH

echo "Building to ${BUILD_DIR}"
./ct-ng build.$(nproc)
