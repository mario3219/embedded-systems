#!/bin/sh 

orig_dir=$(pwd)

cd ../sources

if [ ! -d "busybox/.git" ]; then
  git clone https://git.busybox.net/busybox
fi

cd busybox
mkdir -p ../../build/busybox
make O=../../build/busybox defconfig

cd ../../
cp configs/busybox/defconfig build/busybox/.config
make O=../../build/busybox olddefconfig

src_dir=$(pwd)
export PATH="$src_dir/sources/toolchain/arm-unknown-linux-gnueabihf/bin:$PATH"
cd sources/busybox

make \
    O=../../build/busybox \
    ARCH=arm \
    CROSS_COMPILE=arm-unknown-linux-gnueabihf- \
    -j"$(nproc)"

mkdir -p ../../rootfs/staging

make \
    O=../../build/busybox \
    ARCH=arm \
    CROSS_COMPILE=arm-unknown-linux-gnueabihf- \
    CONFIG_PREFIX="$(realpath ../../rootfs/staging)" \
    install

mkdir -p rootfs/staging/{dev,proc,sys,etc,tmp,run,mnt,root}
chmod 1777 rootfs/staging/tmp
