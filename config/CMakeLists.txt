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

set(CONFIG_LIB "libusbrelaymodule-config")

execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

file(GLOB CFG_FILES "include/*.h.in")

foreach(CFG_FILE IN LISTS CFG_FILES)
    string(REPLACE ".h.in" ".h" SRC_FILE ${CFG_FILE})
    get_filename_component(SRC_FILE ${SRC_FILE} NAME)
    configure_file(${CFG_FILE} ${SRC_FILE} @ONLY)
endforeach()

add_library(libusbrelaymodule-config INTERFACE)

target_include_directories(libusbrelaymodule-config
    INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
    )