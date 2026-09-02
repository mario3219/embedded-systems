#!/bin/bash

SRC_DIR=$(realpath "$(pwd)/../../")
ROOTFS=$(realpath "${SRC_DIR}/rootfs/")

COMPILER="aarch64-unknown-linux-gnu"
SYSROOT=$("${COMPILER}-gcc" -print-sysroot)

APP="${ROOTFS}/staging/usr/local/bin/app"

echo "System root:"
echo "${SYSROOT}"

INTERPRETER=$(
    "${COMPILER}-readelf" -l "${APP}" |
    sed -n 's/.*Requesting program interpreter: \(.*\)]/\1/p' |
    xargs basename
)

mapfile -t NEEDED < <(
    "${COMPILER}-readelf" -d "${APP}" |
    sed -n 's/.*Shared library: \[\(.*\)\]/\1/p'
)

DEPS=("${INTERPRETER}" "${NEEDED[@]}")

LIB_PATHS=()

for lib in "${DEPS[@]}"; do
    [ -z "${lib}" ] && continue

    echo "Searching for ${lib}..."

    while IFS= read -r path; do
        LIB_PATHS+=("${path}")
    done < <(find "${SYSROOT}" -name "${lib}")
done

mkdir -p "${ROOTFS}/staging/lib"

for lib_path in "${LIB_PATHS[@]}"; do
    echo "Copying: ${lib_path}"
    cp -L "${lib_path}" "${ROOTFS}/staging/lib/"
done

# FIX!
# The interpreter expected paths to libraries to be /lib64
mkdir "${ROOTFS}/staging/lib64"
shopt -s extglob
mv ${ROOTFS}/staging/lib/!(${INTERPRETER}) ${ROOTFS}/staging/lib64/

echo
echo "Found interpreter:"
echo "${INTERPRETER}"

echo
echo "Found needed libraries:"
printf '%s\n' "${NEEDED[@]}"
