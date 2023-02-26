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

add_subdirectory(cpp-utils)
add_subdirectory(hidapi)
if(${PROJECT_NAME}_BUILD_SIMU OR ${PROJECT_NAME}_BUILD_GUI)
    set(JSONCPP_WITH_TESTS OFF CACHE BOOL "")
    set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "")
    set(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL "")
    set(JSONCPP_WITH_CMAKE_PACKAGE OFF CACHE BOOL "")
    add_subdirectory(jsoncpp)
endif()
add_subdirectory(liblightargparser)
add_subdirectory(logger)