set(BUILD_HIDAPI build-hidapi)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_custom_target(
        ${BUILD_HIDAPI}
        COMMAND ./bootstrap
        COMMAND ./configure
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/hidapi
    )   
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_custom_target(
        ${BUILD_HIDAPI}
        COMMAND msbuild hidapi.sln -property:Configuration=Release
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/hidapi/windows
    )
endif()