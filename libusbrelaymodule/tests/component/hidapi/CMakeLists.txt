include_directories(
    ${HIDAPI_LIB_INCLUDE}
    ../../../src
    )

add_executable(GetAnyHidDeviceInfoTest 
    GetAnyHidDeviceInfoTest.cpp
    ../../../src/HidapiUtils.cpp
    )

target_link_libraries(GetAnyHidDeviceInfoTest 
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )

add_executable(GetModuleInfoAndRelaysStateTest 
    GetModuleInfoAndRelaysStateTest.cpp
    ../../../src/HidapiUtils.cpp
    )

target_link_libraries(GetModuleInfoAndRelaysStateTest
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )

add_executable(SetRelayStateTest SetRelayStateTest.cpp)
target_link_libraries(SetRelayStateTest
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )

add_executable(SetModuleNameTest SetModuleNameTest.cpp)
target_link_libraries(SetModuleNameTest
    ${HIDAPI_LIB} 
    ${UTILS_LIB}
    )
