if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_custom_target(
        external_hidapi
        COMMAND ./bootstrap
        COMMAND ./configure
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/hidapi
    )

    set(HIDAPI_LIB ${CMAKE_SOURCE_DIR}/external/hidapi/linux/.libs/libhidapi-hidraw.so)
    #set(HIDAPI_LIB ${CMAKE_SOURCE_DIR}/external/hidapi/linux/.libs/libhidapi-hidraw.a)
    
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_custom_target(
        external_hidapi
        COMMAND msbuild hidapi.sln -property:Configuration=Release
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/hidapi/windows
    )

    set(HIDAPI_LIB ${CMAKE_SOURCE_DIR}/external/hidapi/windows/Release/hidapi.lib)
endif()

set(HIDAPI_LIB_INCLUDE ${CMAKE_SOURCE_DIR}/external/hidapi/hidapi)
