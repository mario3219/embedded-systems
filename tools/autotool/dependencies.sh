#!/bin/bash

# DIRECTORIES
SRC_DIR=$(realpath "$(pwd)/../../")
ROOTFS=$(realpath "${SRC_DIR}/rootfs/")
COMPILER="aarch64-unknown-linux-gnu"
SYSROOT=$(${COMPILER}-gcc -print-sysroot)
APP="${ROOTFS}/staging/usr/local/bin/app"
COMPILER="aarch64-unknown-linux-gnu"

echo "System root:"
echo "$SYSROOT"

INTERPRETER=$(
    "${COMPILER}-readelf" -l "${APP}" |
    sed -n 's/.*Requesting program interpreter: \(.*\)]/\1/p' |
    xargs basename
)

NEEDED=$(
    "${COMPILER}-readelf" -d "${APP}" |
    sed -n 's/.*Shared library: \[\(.*\)\]/\1/p'
)

DEPS=("${INTERPRETER}" "${NEEDED[@]}")

LIB_PATHS=()
while IFS= read -r lib; do
    [ -z "${lib}" ] && continue

    echo "Searching for ${lib}..."

    while IFS= read -r path; do
        LIB_PATHS+=("${path}")
    done < <(find "${SYSROOT}" -name "${lib}")

done <<< "${DEPS}"

mkdir -p ${ROOTFS}/staging/lib/

for lib_path in "${LIB_PATHS[@]}"; do
    echo "${lib_path}"
    cp -a ${lib_path} ${ROOTFS}/staging/lib/
done

echo "Found interpreter:"
echo "${INTERPRETER}"
echo "Found needed libraries"
echo "${NEEDED}"
