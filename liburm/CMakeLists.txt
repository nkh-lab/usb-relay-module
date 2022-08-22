file(GLOB SRC_FILES "src/*.cpp")

add_library(${URM_LIB} SHARED ${SRC_FILES})

target_include_directories(${URM_LIB}
    PUBLIC include
    PRIVATE src)
    
target_link_libraries(${URM_LIB}
    PRIVATE hidapi)
