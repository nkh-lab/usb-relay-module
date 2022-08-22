include(${CMAKE_SOURCE_DIR}/cmake/BuildHidapi.cmake)

add_library(${HIDAPI_LIB} SHARED IMPORTED)
add_dependencies(${HIDAPI_LIB} ${BUILD_HIDAPI})

set_property(TARGET ${HIDAPI_LIB} PROPERTY IMPORTED_GLOBAL TRUE)
set_property(TARGET ${HIDAPI_LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/hidapi/hidapi)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set_property(TARGET ${HIDAPI_LIB} PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/hidapi/linux/.libs/libhidapi-hidraw.so)
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    set_property(TARGET ${HIDAPI_LIB} PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/hidapi/windows/Release/hidapi.dll)
    set_property(TARGET ${HIDAPI_LIB} PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/external/hidapi/windows/Release/hidapi.lib)
endif()
