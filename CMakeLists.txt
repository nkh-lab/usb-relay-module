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

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# USB Relay Module
project(usbrelaymodule VERSION 0.0.1)

# External
set(HIDAPI_LIB hidapi::hidapi)

# Main lib
set(USB_RELAY_MODULE_LIB ${PROJECT_NAME})

# Others
# Utils lib
set(UTILS_LIB ${PROJECT_NAME}-utils)
# Config lib
set(CONFIG_LIB ${PROJECT_NAME}-config)                                                                                                                                                                                                
# Main mocked lib
set(USB_RELAY_MODULE_MOCK_LIB ${PROJECT_NAME}-mock)

option(${PROJECT_NAME}_BUILD_CTESTS     "Build component tests"     OFF)
option(${PROJECT_NAME}_BUILD_UTESTS     "Build unit tests"          OFF)
option(${PROJECT_NAME}_BUILD_PORTABLE   "Build portable binaries"   OFF)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    if(${PROJECT_NAME}_BUILD_PORTABLE)
        set(CMAKE_INSTALL_RPATH "\$ORIGIN")
        set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
    endif()

    set(HIDAPI_WITH_LIBUSB OFF)
endif()

add_subdirectory(external)
add_subdirectory(config)
add_subdirectory(utils)
add_subdirectory(libusbrelaymodule)
add_subdirectory(app-cli)
