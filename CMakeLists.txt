cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# USB Relay Module
project(usbrelaymodule)

# External
set(HIDAPI_LIB hidapi)

# Main lib
set(USB_RELAY_MODULE_LIB ${PROJECT_NAME})
set(USB_RELAY_MODULE_LIB ${PROJECT_NAME})

# Others
# Utils lib
set(UTILS_LIB ${PROJECT_NAME}-utils)
# Main mocked lib
set(USB_RELAY_MODULE_MOCK_LIB ${PROJECT_NAME}-mock)

option(${PROJECT_NAME}_BUILD_CTESTS     "Build component tests"     OFF)
option(${PROJECT_NAME}_BUILD_UTESTS     "Build unit tests"          OFF)
option(${PROJECT_NAME}_BUILD_PORTABLE   "Build portable binaries"   OFF)

if(${PROJECT_NAME}_BUILD_PORTABLE AND CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_INSTALL_RPATH "\$ORIGIN")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif()

add_subdirectory(external)
add_subdirectory(utils)
add_subdirectory(libusbrelaymodule)
add_subdirectory(app-cli)