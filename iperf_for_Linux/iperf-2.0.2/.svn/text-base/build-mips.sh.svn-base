#!/bin/sh
make distclean
echo "ac_cv_func_malloc_0_nonnull=yes">mipsel-linux.cache
./configure --host=mipsel-linux CC=mipsel-linux-gcc --cache-file=mipsel-linux.cache
make
