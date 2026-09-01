#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
SOURCES_DIR=$(realpath "${SRC_DIR}/sources/")

REPO_LINK="https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git"

if [ ! -d "${SOURCES_DIR}/linux/.git" ]; then
  cd "${SOURCES_DIR}"
  git clone ${REPO_LINK}  
  git checkout v7.1
fi
