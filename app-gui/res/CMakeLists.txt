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

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(ICON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/relaybox-icon-32.png)
    set(ICON_OUTPUT_NAME icon.o)
    set(ICON_SYM_NAME icon_png)

    # Replace not allowed chars
    string(REPLACE "/" "_" ICON_PATH_UNDERSCORE ${ICON_PATH})
    string(REPLACE "-" "_" ICON_PATH_UNDERSCORE ${ICON_PATH_UNDERSCORE})
    string(REPLACE "." "_" ICON_PATH_UNDERSCORE ${ICON_PATH_UNDERSCORE})

    add_custom_command(
        OUTPUT ${ICON_OUTPUT_NAME}
        COMMAND ld -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/${ICON_OUTPUT_NAME} ${ICON_PATH}
                --defsym=_binary_${ICON_SYM_NAME}_start=_binary_${ICON_PATH_UNDERSCORE}_start
                --defsym=_binary_${ICON_SYM_NAME}_end=_binary_${ICON_PATH_UNDERSCORE}_end
        DEPENDS ${ICON_PATH}
        COMMENT "Generating ${ICON_OUTPUT_NAME}"
    )

    add_library(${PROJECT_NAME}-res OBJECT ${CMAKE_CURRENT_BINARY_DIR}/${ICON_OUTPUT_NAME})
    target_link_libraries(${PROJECT_NAME}-res ${CMAKE_CURRENT_BINARY_DIR}/${ICON_OUTPUT_NAME})

elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_library(${PROJECT_NAME}-res OBJECT resource.rc)
endif()
