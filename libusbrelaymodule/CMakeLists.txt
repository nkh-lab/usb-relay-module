#
# Copyright (C) 2022 https://github.com/nkh-lab
#
# This is free software. You can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 3 as published by the Free Software Foundation.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY.
#
project(libusbrelaymodule)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(${PROJECT_NAME}_BUILD_UTESTS ${usbrelaymodule_BUILD_UTESTS})
set(${PROJECT_NAME}_BUILD_CTESTS ${usbrelaymodule_BUILD_CTESTS})

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

file(GLOB SRC_FILES "src/*.cpp")

if(${usbrelaymodule_BUILD_SIMU})
    file(GLOB SIMU_SRC_FILES "src/simu/*.cpp")
    list(APPEND SRC_FILES ${SIMU_SRC_FILES})
    list(APPEND SIMU_INCLUDES src/simu)
    list(APPEND SIMU_LIBS jsoncpp_lib)
endif()

add_library(${PROJECT_NAME} SHARED
    ${SRC_FILES}
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PRIVATE src
    PRIVATE ${SIMU_INCLUDES}
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE hidapi::hidapi
    PRIVATE libcpputils
    PRIVATE ${SIMU_LIBS}
    )

add_subdirectory(tests)
