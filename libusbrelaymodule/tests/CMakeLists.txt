if (${PROJECT_NAME}_BUILD_UTESTS )
    add_subdirectory(unit)
endif()

if (${PROJECT_NAME}_BUILD_CTESTS )
    add_subdirectory(component)
endif()