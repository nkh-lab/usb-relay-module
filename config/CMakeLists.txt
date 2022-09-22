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

file(GLOB CFG_FILES "include/*.h.in")

foreach(CFG_FILE IN LISTS CFG_FILES)
    string(REPLACE ".h.in" ".h" SRC_FILE ${CFG_FILE})
    get_filename_component(SRC_FILE ${SRC_FILE} NAME)
    configure_file(${CFG_FILE} ${SRC_FILE} @ONLY)
endforeach()

add_library(${CONFIG_LIB} INTERFACE)

target_include_directories(${CONFIG_LIB} 
    INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
    )