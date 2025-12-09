#!/bin/sh
# Create symlink in the final rootfs
ln -sf /lib/ld-2.21.so "${TARGET_DIR}/lib/ld-linux.so.3"
