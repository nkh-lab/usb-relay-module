include_directories(${HIDAPI_LIB_INCLUDE})

add_executable(GetAnyHidDeviceInfoTest GetAnyHidDeviceInfoTest.cpp)
add_dependencies(GetAnyHidDeviceInfoTest external_hidapi)
target_link_libraries(GetAnyHidDeviceInfoTest ${HIDAPI_LIB} ${PROJECT_NAME}-headers ${PROJECT_NAME}-utils)

add_executable(GetModuleInfoAndRelaysStateTest GetModuleInfoAndRelaysStateTest.cpp)
add_dependencies(GetModuleInfoAndRelaysStateTest external_hidapi)
target_link_libraries(GetModuleInfoAndRelaysStateTest ${HIDAPI_LIB} ${PROJECT_NAME}-headers ${PROJECT_NAME}-utils)

add_executable(SetRelayStateTest SetRelayStateTest.cpp)
add_dependencies(SetRelayStateTest external_hidapi)
target_link_libraries(SetRelayStateTest ${HIDAPI_LIB} ${PROJECT_NAME}-headers ${PROJECT_NAME}-utils)
