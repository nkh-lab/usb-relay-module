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

include_directories(
    ../../../src
    ../../../include
    )

add_executable(GetAnyHidDeviceInfoTest
    GetAnyHidDeviceInfoTest.cpp
    ../../../src/HidapiUtils.cpp
    )

target_link_libraries(GetAnyHidDeviceInfoTest
    hidapi::hidapi
    libcpputils
    )

add_executable(GetModuleInfoAndRelaysStateTest
    GetModuleInfoAndRelaysStateTest.cpp
    ../../../src/HidapiUtils.cpp
    )

target_link_libraries(GetModuleInfoAndRelaysStateTest
    hidapi::hidapi
    libcpputils
    )

add_executable(SetRelayStateTest SetRelayStateTest.cpp)
target_link_libraries(SetRelayStateTest
    hidapi::hidapi
    libcpputils
    )

add_executable(SetModuleNameTest SetModuleNameTest.cpp)
target_link_libraries(SetModuleNameTest
    hidapi::hidapi
    libcpputils
    )
