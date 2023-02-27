#
# Copyright (C) 2023 https://github.com/nkh-lab
#
# This is free software. You can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 3 as published by the Free Software Foundation.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY.
#

project(app-gui)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    ### wxWidgets ###
    # Defines
    add_definitions(-D__WXGTK__)
    # Suppress warnings
    add_compile_options(-Wno-deprecated-copy)
    add_compile_options(-Wno-ignored-qualifiers)
    #################
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_definitions(-D__PRETTY_FUNCTION__=__FUNCSIG__)

    ### wxWidgets ###
    # Support find_package(wxWidgets REQUIRED) as prebuilt
    set(wxWidgets_ROOT_DIR ${CMAKE_SOURCE_DIR}/prebuilt/wxwidgets)
    set(wxWidgets_LIB_DIR ${CMAKE_SOURCE_DIR}/prebuilt/wxwidgets/lib/Debug)
    set(wxWidgets_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/prebuilt/wxwidgets/include)
    # Defines
    add_definitions(-DWXUSINGDLL)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # Link options
    add_link_options(/SUBSYSTEM:WINDOWS)
    #################
endif()

find_package(wxWidgets REQUIRED)

set(APP_GUI_NAME relaybox)

set(${PROJECT_NAME}_BUILD_UTESTS ${usbrelaymodule_BUILD_UTESTS})

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

file(GLOB SRC_FILES
    "src/*.cpp"
    "src/widgets/*.cpp"
    )

add_executable(${APP_GUI_NAME}
    ${SRC_FILES}
    )

target_include_directories(${APP_GUI_NAME}
    PRIVATE src
    PRIVATE ${wxWidgets_INCLUDE_DIRS}
    )

target_link_libraries(${APP_GUI_NAME}
    PRIVATE libcpputils
    PRIVATE ${wxWidgets_LIBRARIES}
    PRIVATE libusbrelaymodule
    PRIVATE libusbrelaymodule-config
    PRIVATE nkhlablogger
    PRIVATE jsoncpp_lib
    )

add_subdirectory(tests)
