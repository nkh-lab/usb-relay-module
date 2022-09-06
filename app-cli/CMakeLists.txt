add_executable(getrelay 
    src/getrelay.cpp
    src/GetRelayWorker.cpp
    src/TextUserInterface.cpp
    )

target_link_libraries(getrelay
    ${UTILS_LIB}
    ${USB_RELAY_MODULE_LIB}
    lightargparser
    )

add_executable(setrelay
    src/setrelay.cpp
    )

target_link_libraries(setrelay 
    ${UTILS_LIB}
    ${USB_RELAY_MODULE_LIB}
    )

add_subdirectory(tests)
