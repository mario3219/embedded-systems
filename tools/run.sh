#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../")

KERNEL="build/linux/arch/arm64/boot/Image"
INITRD="rootfs/images/rootfs.cpio.gz"

cd ${SRC_DIR}

qemu-system-arm64 \
    -M virt \
    -cpu cortex-a53 \
    -m 512M \
    -kernel  ${KERNEL} \
    -initrd  ${INITRD} \
    -append "console=ttyAMA0 earlycon=pl011,0x09000000 keep_bootcon rdinit=/init ignore_loglevel loglevel=8 initcall_debug" \
    -serial mon:stdio \
    -monitor none \
    -display none
