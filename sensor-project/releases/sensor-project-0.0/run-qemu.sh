#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

qemu-system-arm \
    -M virt \
    -cpu cortex-a15 \
    -m 256M \
    -kernel "$SCRIPT_DIR/zImage" \
    -initrd "$SCRIPT_DIR/rootfs.cpio.gz" \
    -append "console=ttyAMA0 rdinit=/init" \
    -nographic
