include_directories(${HIDAPI_LIB_INCLUDE})

add_executable(GetRelayInfoTest GetRelayInfoTest.cpp)
add_dependencies(GetRelayInfoTest external_hidapi)
target_link_libraries(GetRelayInfoTest ${HIDAPI_LIB} ${PROJECT_NAME}-headers)
