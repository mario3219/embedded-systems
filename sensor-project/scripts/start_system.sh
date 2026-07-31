#!/bin/bash

SCRIPT_DIR=$(pwd)
cd $SCRIPT_DIR/../

#qemu-system-arm \
#    -M vexpress-a15 \
#    -m 512M \
#    -kernel build/linux/arch/arm/boot/zImage \
#    -dtb build/linux/arch/arm/boot/dts/arm/vexpress-v2p-ca15-tc1.dtb \
#    -initrd rootfs/images/rootfs.cpio.gz \
#    -append "earlycon=pl011,0x1c090000 console=ttyAMA0,38400 rdinit=/init loglevel=8" \
#    -serial mon:stdio \
#    -display none \
#    -no-reboot

qemu-system-arm \
    -M virt \
    -cpu cortex-a15 \
    -m 512M \
    -kernel build/linux/arch/arm/boot/zImage \
    -initrd rootfs/images/rootfs.cpio.gz \
    -append "console=ttyAMA0 earlycon=pl011,0x09000000 keep_bootcon rdinit=/init ignore_loglevel loglevel=8 initcall_debug" \
    -serial mon:stdio \
    -monitor none \
    -display none

cd $SCRIPT_DIR
