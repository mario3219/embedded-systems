#!/bin/bash

SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

cd $SRC_DIR/sources/linux/
make O=../../build/linux ARCH=arm savedefconfig
cp $SRC_dir/build/linux/defconfig $SRC_DIR/configs/kernel_defconfig
