#!/bin/bash

SRC_DIR=$(realpath "$(pwd)/")
CROSS_DIR=$(realpath "${SRC_DIR}/../../sources/crosstool-ng-1.28.0/")

cd ${CROSS_DIR}
./ct-ng distclean
