#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR=$(realpath "${SRC_DIR}/../sources/")

# WEB LINKS
CROSS_LINK="http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.28.0.tar.xz"

mkdir -p $SOURCES_DIR

if [ ! -d "$SOURCES_DIR/crosstool-ng-1.28.0" ]; then
  if [ ! -f "$SOURCES_DIR/crosstool-ng-1.28.0.tar.xz" ]; then
    wget -P "$SOURCES_DIR/" "$CROSS_LINK"
  fi
  tar -xvf "$SOURCES_DIR/crosstool-ng-1.28.0.tar.xz" -C "$SOURCES_DIR/"
fi

cd $SOURCES_DIR/crosstool-ng-1.28.0/
export PATH="/usr/bin:/bin:$PATH"
./bootstrap
./configure --enable-local
make

echo "${SOURCES_DIR}"
