cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

project(nrelay)

include(cmake/ExternalHidapi.cmake)

option(${PROJECT_NAME}_BUILD_CTESTS "Build component tests" off)
option(${PROJECT_NAME}_BUILD_UTESTS "Build unit tests" off)

add_subdirectory(src)

if (${PROJECT_NAME}_BUILD_CTESTS )
    add_subdirectory(tests/component)
endif()

if (${PROJECT_NAME}_BUILD_UNITTESTS)
    add_subdirectory(test/unit)
endif()