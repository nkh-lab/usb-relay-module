#!/bin/bash

find . \( -name "*.cpp" -o -name "*.h" \) -not \( -path "./external/*" -o -path "./build/*" \) | xargs clang-format -i