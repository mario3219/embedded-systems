#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../")

cd ${SRC_DIR}
autoreconf --install
