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

project(app-cli)

set(${PROJECT_NAME}_BUILD_UTESTS ${usbrelaymodule_BUILD_UTESTS})

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(getrelay
    src/getrelay.cpp
    src/GetRelayWorker.cpp
    src/TextUserInterface.cpp
    )

target_link_libraries(getrelay
    libusbrelaymodule-utils
    libusbrelaymodule-config
    libusbrelaymodule
    liblightargparser
    )

add_executable(setrelay
    src/setrelay.cpp
    src/SetRelayWorker.cpp
    src/TextUserInterface.cpp
    )

target_link_libraries(setrelay
    libusbrelaymodule-utils
    libusbrelaymodule-config
    libusbrelaymodule
    liblightargparser
    )

add_subdirectory(tests)
