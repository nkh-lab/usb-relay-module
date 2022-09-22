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

# -fPIC to be able to link static lib to shared
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -fPIC")
endif()

file(GLOB SRC_FILES "src/*.cpp")

add_library(${UTILS_LIB} STATIC 
    ${SRC_FILES})

target_include_directories(${UTILS_LIB}
    PUBLIC include)
