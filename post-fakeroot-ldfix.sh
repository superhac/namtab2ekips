#!/bin/sh
# Create symlink in the final rootfs
ln -sf /lib/ld-2.23.so "${TARGET_DIR}/lib/ld-linux.so.3"
