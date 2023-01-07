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

# -I - include
# -i - ignore
# --check-config - use it only for check configuration, e.g. what includes are missed

cppcheck ./ --inconclusive --enable=all --suppress=missingIncludeSystem --suppress=functionStatic \
        -I external/hidapi/hidapi \
        -I external/liblightargparser/include \
        -I build/config \
        -I app-cli/src \
        -I libusbrelaymodule/include \
        -I libusbrelaymodule/src \
        -I libusbrelaymodule/tests/unit/mock \
        -I utils/include \
        -i doc \
        -i build \
        -i external \
        -i tools
