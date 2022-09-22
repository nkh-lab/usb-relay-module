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

add_executable(getrelay 
    src/getrelay.cpp
    src/GetRelayWorker.cpp
    src/TextUserInterface.cpp
    )

target_link_libraries(getrelay
    ${UTILS_LIB}
    ${CONFIG_LIB}
    ${USB_RELAY_MODULE_LIB}
    lightargparser
    )

add_executable(setrelay
    src/setrelay.cpp
    src/SetRelayWorker.cpp
    src/TextUserInterface.cpp
    )

target_link_libraries(setrelay 
    ${UTILS_LIB}
    ${CONFIG_LIB}
    ${USB_RELAY_MODULE_LIB}
    lightargparser
    )

add_subdirectory(tests)
