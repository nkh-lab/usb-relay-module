#!/bin/bash

find . \( -name "*.cpp" -o -name "*.h" -o -name "*.in" \) -not \( -path "./external/*" -o -path "./build/*" \) | xargs clang-format -i