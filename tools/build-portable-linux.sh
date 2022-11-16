#!/bin/bash

#
# Copyright (C) 2022 https://github.com/nkh-lab
#
# This is free software. You can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 3 as published by the Free Software Foundation.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY.
#

DIR=$(cd "$(dirname "$0")" && pwd)

PROJECT_ROOT=$(cd $DIR/.. && pwd)
PORTABLE_DIR_REL_PATH="build/portable"
PORTABLE_ARCHIVE_NAME="usbrelaymodule-portable"

rm -rf build/
mkdir build && cd build

cmake -Dusbrelaymodule_BUILD_PORTABLE=ON ..
make

cd $PROJECT_ROOT

mkdir $PORTABLE_DIR_REL_PATH
cp build/app-cli/getrelay $PORTABLE_DIR_REL_PATH
cp build/app-cli/setrelay $PORTABLE_DIR_REL_PATH
cp build/libusbrelaymodule/libusbrelaymodule.so $PORTABLE_DIR_REL_PATH
cp build/external/hidapi/src/linux/libhidapi-hidraw.so $PORTABLE_DIR_REL_PATH

cd $PORTABLE_DIR_REL_PATH

ln -s libhidapi-hidraw.so libhidapi-hidraw.so.0

#zip -r ../$PORTABLE_ARCHIVE_NAME.zip *
tar -czf ../$PORTABLE_ARCHIVE_NAME.tar.gz *