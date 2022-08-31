add_executable(getrelay 
    src/getrelay.cpp
    src/GetRelayWorker.cpp)

target_link_libraries(getrelay
    ${UTILS_LIB}
    ${USB_RELAY_MODULE}
    lightargparser)

add_executable(setrelay src/setrelay.cpp)
target_link_libraries(setrelay 
    ${UTILS_LIB}
    ${USB_RELAY_MODULE})
