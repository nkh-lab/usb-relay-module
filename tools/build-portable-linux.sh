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

CMAKE_ARGS="-Dusbrelaymodule_BUILD_PORTABLE=ON"

for arg in "$@"
do
    if [ "simu" = "$arg" ]; then
        SIMU="true"
        CMAKE_ARGS="$CMAKE_ARGS \
                    -Dusbrelaymodule_BUILD_SIMU=ON"
    fi
    if [ "gui" = "$arg" ]; then
        GUI="true"
        CMAKE_ARGS="$CMAKE_ARGS \
                    -Dusbrelaymodule_BUILD_GUI=ON"
    fi
done

git submodule update --init

rm -rf build/

mkdir build && cd build

cmake $CMAKE_ARGS ..
make

# Check if build return error
if [ $? -ne 0 ]; then
  exit $?
fi

cd $PROJECT_ROOT

mkdir $PORTABLE_DIR_REL_PATH
cp build/app-cli/getrelay $PORTABLE_DIR_REL_PATH
cp build/app-cli/setrelay $PORTABLE_DIR_REL_PATH
cp build/libusbrelaymodule/libusbrelaymodule.so $PORTABLE_DIR_REL_PATH
cp build/external/hidapi/src/linux/libhidapi-hidraw.so* $PORTABLE_DIR_REL_PATH
if [ "$SIMU" = "true" ]; then
    cp build/external/jsoncpp/src/lib_json/libjsoncpp.so* $PORTABLE_DIR_REL_PATH
fi
if [ "$GUI" = "true" ]; then
    cp build/app-gui/relaybox $PORTABLE_DIR_REL_PATH
    cp build/external/jsoncpp/src/lib_json/libjsoncpp.so* $PORTABLE_DIR_REL_PATH
fi

cd $PORTABLE_DIR_REL_PATH

#zip -r ../$PORTABLE_ARCHIVE_NAME.zip *
tar -czf ../$PORTABLE_ARCHIVE_NAME.tar.gz *