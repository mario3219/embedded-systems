#!/bin/bash

SRC_DIR=$(realpath "$(pwd)/../")

DOWNLOAD_LINK="https://physionet.org/files/nstdb/1.0.0/"

mkdir -p $SRC_DIR/data/
cd $SRC_DIR/data/

if [ ! -d "physionet.org" ]; then
  wget -r -N -c -np $DOWNLOAD_LINK
fi

cp ${SRC_DIR}/data/physionet.org/files/nstdb/1.0.0/118e00.dat .
