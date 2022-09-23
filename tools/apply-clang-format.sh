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

find . \( -name "*.cpp" -o -name "*.h" -o -name "*.in" \) -not \( -path "./external/*" -o -path "./build/*" \) | xargs clang-format -i