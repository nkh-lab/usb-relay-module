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

option(${PROJECT_NAME}_BUILD_CTESTS "Build component tests" off)
option(${PROJECT_NAME}_BUILD_UTESTS "Build unit tests" off)

add_subdirectory(external)
add_subdirectory(utils)
add_subdirectory(libusbrelaymodule)
add_subdirectory(app-cli)