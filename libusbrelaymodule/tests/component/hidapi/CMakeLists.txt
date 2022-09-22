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

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

include_directories(
    ${HIDAPI_LIB_INCLUDE}
    ../../../src
    ../../../include
    )

add_executable(GetAnyHidDeviceInfoTest 
    GetAnyHidDeviceInfoTest.cpp
    ../../../src/HidapiUtils.cpp
    )

target_link_libraries(GetAnyHidDeviceInfoTest 
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )

add_executable(GetModuleInfoAndRelaysStateTest 
    GetModuleInfoAndRelaysStateTest.cpp
    ../../../src/HidapiUtils.cpp
    )

target_link_libraries(GetModuleInfoAndRelaysStateTest
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )

add_executable(SetRelayStateTest SetRelayStateTest.cpp)
target_link_libraries(SetRelayStateTest
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )

add_executable(SetModuleNameTest SetModuleNameTest.cpp)
target_link_libraries(SetModuleNameTest
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )
