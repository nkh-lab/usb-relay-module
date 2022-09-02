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
    PRIVATE ${PROJECT_NAME}
    PRIVATE ${GTEST_LIBRARIES}
    PRIVATE GTest::Main
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    PRIVATE lightargparser
    PRIVATE ${UTILS_LIB}
    )

target_include_directories(AppCliUnitTests
    PRIVATE "../../src"
    )