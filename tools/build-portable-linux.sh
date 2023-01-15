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
                    -Dusbrelaymodule_BUILD_SIMU=ON \
                    -DJSONCPP_WITH_TESTS=OFF  \
                    -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF \
                    -DJSONCPP_WITH_PKGCONFIG_SUPPORT=OFF \
                    -DJSONCPP_WITH_CMAKE_PACKAGE=OFF"

        if [ ! -d "$PROJECT_ROOT/external/jsoncpp" ]; then
            git clone https://github.com/nkh-lab/jsoncpp.git ./external/jsoncpp -b Avoid-using-cmake-glob-vars
        fi
    fi
done

rm -rf build/
mkdir build && cd build

cmake $CMAKE_ARGS ..
make

cd $PROJECT_ROOT

mkdir $PORTABLE_DIR_REL_PATH
cp build/app-cli/getrelay $PORTABLE_DIR_REL_PATH
cp build/app-cli/setrelay $PORTABLE_DIR_REL_PATH
cp build/libusbrelaymodule/libusbrelaymodule.so $PORTABLE_DIR_REL_PATH
cp build/external/hidapi/src/linux/libhidapi-hidraw.so* $PORTABLE_DIR_REL_PATH
if [ $SIMU = "true" ]; then
    cp build/external/jsoncpp/src/lib_json/libjsoncpp.so* $PORTABLE_DIR_REL_PATH
fi

cd $PORTABLE_DIR_REL_PATH

#zip -r ../$PORTABLE_ARCHIVE_NAME.zip *
tar -czf ../$PORTABLE_ARCHIVE_NAME.tar.gz *