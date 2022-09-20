if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
endif()

find_package(GTest REQUIRED)

file(GLOB SRC_FILES 
    "*.cpp" 
    "../../src/GetRelayWorker.cpp"
    "../../src/SetRelayWorker.cpp"
    "../../src/TextUserInterface.cpp"
    )

add_executable(AppCliUnitTests
    ${SRC_FILES}
    )

target_link_libraries(AppCliUnitTests
    ${USB_RELAY_MODULE_LIB}
    ${USB_RELAY_MODULE_MOCK_LIB}
    ${GTEST_LIBRARIES}
    GTest::Main
    gmock
    ${CMAKE_THREAD_LIBS_INIT}
    lightargparser
    ${UTILS_LIB}
    ${CONFIG_LIB}
    )

target_include_directories(AppCliUnitTests
    PRIVATE "../../src"
    )
