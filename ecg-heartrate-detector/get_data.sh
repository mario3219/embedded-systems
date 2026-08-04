#!/bin/bash

SRC_DIR=$(realpath "$(pwd)/")
TARGET_DIR="${SRC_DIR}/data/"

DOWNLOAD_LINK="https://physionet.org/files/nstdb/1.0.0/"

mkdir -p $TARGET_DIR
cd $TARGET_DIR

if [ ! -d "physionet.org" ]; then
  wget -r -N -c -np $DOWNLOAD_LINK
fi

cd $SRC_DIR
python3 process_data.py
