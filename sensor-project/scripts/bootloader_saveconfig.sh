#!/bin/bash

SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

cd $SRC_DIR/sources/u-boot/
make savedefconfig
cp defconfig $SRC_DIR/configs/custom_qemu_arm_defconfig
