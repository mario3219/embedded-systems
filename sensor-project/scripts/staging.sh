#!/bin/sh 

orig_dir=$(pwd)
cd ../
cp scripts/init rootfs/staging/
chmod u+x rootfs/staging/init
mkdir -p rootfs/images
cd rootfs/staging
find . -print0 \
    | cpio --null -ov --format=newc \
    | gzip -9 > ../images/rootfs.cpio.gz
