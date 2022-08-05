if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_custom_target(
        external_hidapi
        COMMAND ./bootstrap
        COMMAND ./configure
        COMMAND make
        WORKING_DIRECTORY ../external/hidapi
    )

    set(HIDAPI_LIB ${CMAKE_SOURCE_DIR}/external/hidapi/linux/.libs/libhidapi-hidraw.so)
    #set(HIDAPI_LIB ${CMAKE_SOURCE_DIR}/external/hidapi/linux/.libs/libhidapi-hidraw.a)
    
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_custom_target(
        external_hidapi
        COMMAND msbuild hidapi.sln
        WORKING_DIRECTORY ../external/hidapi/windows
    )
endif()

set(HIDAPI_LIB_INCLUDE ${CMAKE_SOURCE_DIR}/external/hidapi/hidapi)
