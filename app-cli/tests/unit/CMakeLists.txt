find_package(GTest REQUIRED)

file(GLOB SRC_FILES 
    "*.cpp" 
    "../../src/GetRelayWorker.cpp"
    "../../src/TextUserInterface.cpp"
    )

add_executable(AppCliUnitTests
    ${SRC_FILES}
    )

target_link_libraries(AppCliUnitTests
    PRIVATE ${USB_RELAY_MODULE_LIB}
    PRIVATE ${USB_RELAY_MODULE_MOCK_LIB}
    PRIVATE ${GTEST_LIBRARIES}
    PRIVATE GTest::Main
    PRIVATE gmock
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    PRIVATE lightargparser
    PRIVATE ${UTILS_LIB}
    )

target_include_directories(AppCliUnitTests
    PRIVATE "../../src"
    )
