if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

file(GLOB SRC_FILES "src/*.cpp")

add_library(${UTILS_LIB} STATIC 
    ${SRC_FILES})

target_include_directories(${UTILS_LIB}
    PUBLIC include)
