cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

# USB Relay Module
project(usbrelaymodule)

# External
set(HIDAPI_LIB hidapi)

# Main lib
set(USB_RELAY_MODULE_LIB ${PROJECT_NAME})
set(USB_RELAY_MODULE_LIB ${PROJECT_NAME})

# Others
# General utils
set(UTILS_LIB ${PROJECT_NAME}-utils)
# HIDAPI C++ wrapper + utils
set(HIDAPICPP_LIB ${HIDAPI_LIB}-cpp)
# Main mocked lib
set(USB_RELAY_MODULE_MOCK_LIB ${PROJECT_NAME}-mock)

option(${PROJECT_NAME}_BUILD_CTESTS "Build component tests" off)
option(${PROJECT_NAME}_BUILD_UTESTS "Build unit tests" off)

file(GLOB SUBDIRS
    "external"
    "lib*"
    "app*"
    )

foreach(X IN LISTS SUBDIRS)
    if(IS_DIRECTORY ${X})
        add_subdirectory(${X})
    endif()
endforeach()