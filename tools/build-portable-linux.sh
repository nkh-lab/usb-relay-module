#!/bin/bash

DIR=$(cd "$(dirname "$0")" && pwd)

PROJECT_ROOT=$(cd $DIR/.. && pwd)
PORTABLE_DIR_REL_PATH="build/portable"

rm -rf build/
mkdir build && cd build

cmake -Dusbrelaymodule_BUILD_PORTABLE=ON ..
make

cd $PROJECT_ROOT

mkdir $PORTABLE_DIR_REL_PATH
cp build/app-cli/getrelay $PORTABLE_DIR_REL_PATH
cp build/app-cli/setrelay $PORTABLE_DIR_REL_PATH
cp build/libusbrelaymodule/libusbrelaymodule.so $PORTABLE_DIR_REL_PATH
cp external/hidapi/linux/.libs/libhidapi-hidraw.so $PORTABLE_DIR_REL_PATH

cd $PORTABLE_DIR_REL_PATH

zip -r ../usbrelaymodule-portable.zip *