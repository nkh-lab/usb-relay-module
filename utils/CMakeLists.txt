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

project(libusbrelaymodule-utils)

set(CMAKE_STATIC_LIBRARY_PREFIX "")

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    # -fPIC to be able to link static lib to shared
    add_compile_options(-fPIC)
endif()

file(GLOB SRC_FILES "src/*.cpp")

add_library(${PROJECT_NAME} STATIC
    ${SRC_FILES}
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC include
    )

add_library(${PROJECT_NAME}-headers INTERFACE)

target_include_directories(${PROJECT_NAME}-headers
    INTERFACE include
    )