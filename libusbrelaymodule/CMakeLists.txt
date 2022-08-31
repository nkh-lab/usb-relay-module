file(GLOB SRC_FILES "src/*.cpp")

add_library(${USB_RELAY_MODULE} SHARED ${SRC_FILES})

target_include_directories(${USB_RELAY_MODULE}
    PUBLIC include
    PRIVATE src)
    
target_link_libraries(${USB_RELAY_MODULE}
    PRIVATE hidapi)

add_subdirectory(tests)
