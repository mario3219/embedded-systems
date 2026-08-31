#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR="${SRC_DIR}/../sources/"

# WEB LINKS
CROSS_LINK="http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.28.0.tar.xz"

mkdir -p $SOURCES_DIR

if [ ! -d "$SOURCES_DIR/crosstool-ng-1.28.0" ]; then
  cd "crosstool/"
  ./get_crosstool.sh
fi
