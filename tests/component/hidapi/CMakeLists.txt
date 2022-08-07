include_directories(${HIDAPI_LIB_INCLUDE})

add_executable(GetAnyHidDeviceInfoTest GetAnyHidDeviceInfoTest.cpp)
add_dependencies(GetAnyHidDeviceInfoTest external_hidapi)
target_link_libraries(GetAnyHidDeviceInfoTest ${HIDAPI_LIB} ${PROJECT_NAME}-headers ${PROJECT_NAME}-utils)

add_executable(GetRelayStateTest GetRelayStateTest.cpp)
add_dependencies(GetRelayStateTest external_hidapi)
target_link_libraries(GetRelayStateTest ${HIDAPI_LIB} ${PROJECT_NAME}-headers ${PROJECT_NAME}-utils)

add_executable(SetRelayStateTest SetRelayStateTest.cpp)
add_dependencies(SetRelayStateTest external_hidapi)
target_link_libraries(SetRelayStateTest ${HIDAPI_LIB} ${PROJECT_NAME}-headers ${PROJECT_NAME}-utils)
