include_directories(${HIDAPI_LIB_INCLUDE})

add_library(${PROJECT_NAME}-headers INTERFACE)
target_include_directories(${PROJECT_NAME}-headers INTERFACE include)

add_library(${PROJECT_NAME}-utils STATIC utils/utils.cpp)
target_include_directories(${PROJECT_NAME}-utils PUBLIC utils)

add_executable(getrelay getrelay.cpp)
add_dependencies(getrelay external_hidapi)
target_link_libraries(getrelay ${HIDAPI_LIB} ${PROJECT_NAME}-utils)

add_executable(setrelay setrelay.cpp)
add_dependencies(setrelay external_hidapi)
target_link_libraries(setrelay ${HIDAPI_LIB} ${PROJECT_NAME}-utils)
