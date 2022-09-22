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

file(GLOB SRC_FILES "src/*.cpp")

add_library(${USB_RELAY_MODULE_LIB} SHARED
    ${SRC_FILES}
    )

target_include_directories(${USB_RELAY_MODULE_LIB}
    PUBLIC include
    PRIVATE src
    )
    
target_link_libraries(${USB_RELAY_MODULE_LIB}
    PRIVATE ${HIDAPI_LIB}
    PRIVATE ${UTILS_LIB}
    )

add_subdirectory(tests)
