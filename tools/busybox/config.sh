#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
BUSYBOX_DIR=$(realpath "${SRC_DIR}/../../sources/busybox/")

cd ${BUSYBOX_DIR}
make O=../../build/busybox menuconfig
