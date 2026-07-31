#!/bin/bash

SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

cp $SRC_DIR/build/busybox/.config $SRC_DIR/configs/busybox_defconfig
