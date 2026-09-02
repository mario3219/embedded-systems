#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../")
APP_PATH="${SRC_DIR}/code/ecg-sensor/build/"

cd ${APP_PATH}
./app
