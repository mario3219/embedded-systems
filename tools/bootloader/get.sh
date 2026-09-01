#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/")
SOURCES_DIR=$(realpath "${SRC_DIR}/../../sources/")
REPO_LINK="https://git.u-boot-project.org/u-boot/u-boot.git"

if [ ! -d "${SOURCES_DIR}/u-boot/.git" ]; then
  cd "${SOURCES_DIR}"
  git clone ${REPO_LINK}
fi

echo "Cloned repo to ${SOURCES_DIR}/u-boot/"
