file(GLOB SRC_FILES "src/*.cpp")

add_library(${HIDAPICPP_LIB} STATIC 
    ${SRC_FILES})

target_include_directories(${HIDAPICPP_LIB}
    PUBLIC include)

target_link_libraries(${HIDAPICPP_LIB}
    PUBLIC ${UTILS_LIB}
    PUBLIC ${HIDAPI_LIB})