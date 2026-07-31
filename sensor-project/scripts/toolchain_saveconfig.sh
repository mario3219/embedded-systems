#!/bin/bash

SCRIPT_DIR=$(pwd)
cd ../sources/crosstool-ng-1.28.0
./ct-ng savedefconfig
cp defconfig ../../configs/toolchain_defconfig
