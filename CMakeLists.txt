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

cmake_minimum_required(VERSION 3.4.1)

# USB Relay Module
project(usbrelaymodule VERSION 2.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(${PROJECT_NAME}_BUILD_CTESTS     "Build component tests"     OFF)
option(${PROJECT_NAME}_BUILD_UTESTS     "Build unit tests"          OFF)
option(${PROJECT_NAME}_BUILD_PORTABLE   "Build portable binaries"   OFF)
option(${PROJECT_NAME}_BUILD_SIMU       "Build in simulation mode"  OFF)
option(${PROJECT_NAME}_BUILD_GUI        "Build GUI application"     OFF)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    if(${PROJECT_NAME}_BUILD_PORTABLE)
        set(CMAKE_INSTALL_RPATH "\$ORIGIN")
        set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
    endif()

    set(HIDAPI_WITH_LIBUSB OFF)
endif()

if(${PROJECT_NAME}_BUILD_SIMU)
    add_definitions(-DURM_SIMU)
endif()

set(LOGGER_BUILD_HEADER_LIB ON CACHE BOOL "Build the header only library")

add_subdirectory(external)
add_subdirectory(config)
add_subdirectory(libusbrelaymodule)
add_subdirectory(app-cli)
if(${PROJECT_NAME}_BUILD_GUI)
    add_subdirectory(app-gui)
endif()
