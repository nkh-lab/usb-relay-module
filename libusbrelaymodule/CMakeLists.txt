file(GLOB SRC_FILES "src/*.cpp")

add_library(${USB_RELAY_MODULE_LIB} SHARED
    ${SRC_FILES}
    )

target_include_directories(${USB_RELAY_MODULE_LIB}
    PUBLIC include
    PRIVATE src
    )
    
target_link_libraries(${USB_RELAY_MODULE_LIB}
    PRIVATE hidapi
    ${UTILS_LIB}
    )

add_subdirectory(tests)
