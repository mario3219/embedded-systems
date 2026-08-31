#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR=$(realpath "${SRC_DIR}/../../sources/")

if [ ! -d "${SOURCES_DIR}/u-boot/.git" ]; then
  cd "${SOURCES_DIR}"
  git clone https://git.u-boot-project.org/u-boot/u-boot.git
fi

echo "Cloned repo to ${SOURCES_DIR}/u-boot/"
