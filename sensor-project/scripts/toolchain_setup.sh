#!/bin/bash

# DIRECTORIES
SCRIPT_DIR=$(pwd)
SRC_DIR=$(realpath "$SCRIPT_DIR/..")

# WEB LINKS
CROSS_LINK="http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.28.0.tar.xz"

# toolchain config has PREFIX_PATH using $SRC_DIR
export SRC_DIR

if [ ! -d "$SRC_DIR/sources/crosstool-ng-1.28.0" ]; then
  
  if [ ! -f "$SRC_DIR/sources/crosstool-ng-1.28.0.tar.xz" ]; then
    wget -P $SRC_DIR/sources/ $CROSS_LINK
  fi
  
  tar -xvf $SRC_DIR/sources/crosstool-ng-1.28.0.tar.xz -C $SRC_DIR/sources/
  cd $SRC_DIR/sources/crosstool-ng-1.28.0
  ./bootstrap
  ./configure --enable-local
  make

fi

cd $SRC_DIR
mkdir -p sources/toolchain
cp configs/toolchain_defconfig sources/crosstool-ng-1.28.0/.config
cd sources/crosstool-ng-1.28.0
./ct-ng olddefconfig
./ct-ng build
