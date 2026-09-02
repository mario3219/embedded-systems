#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../")

KERNEL="build/linux/arch/arm64/boot/Image"
INITRD="rootfs/images/rootfs.cpio.gz"

cd ${SRC_DIR}

qemu-system-aarch64 \
    -machine virt \
    -cpu cortex-a53 \
    -m 512M \
    -kernel "${KERNEL}" \
    -initrd "${INITRD}" \
    -append "console=ttyAMA0 rdinit=/init" \
    -nographic \
    -chardev socket,id=ecg,path=/tmp/ecg.sock,server=on,wait=off \
    -device virtio-serial-device \
    -device virtserialport,chardev=ecg,name=ecg \
    -fsdev local,id=hostshare,path="${SRC_DIR}/data/qemu-output",security_model=none \
    -device virtio-9p-device,fsdev=hostshare,mount_tag=hostshare
