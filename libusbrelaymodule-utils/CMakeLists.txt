file(GLOB SRC_FILES "src/*.cpp")

add_library(${UTILS_LIB} STATIC 
    ${SRC_FILES})

target_include_directories(${UTILS_LIB}
    PUBLIC include)
