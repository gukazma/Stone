file(GLOB SOURCES Source/*.cpp)
file(GLOB INCLUDES Include/*.h)
add_library(DetourCrowd ${SOURCES} ${INCLUDES})

add_library(RecastNavigation::DetourCrowd ALIAS DetourCrowd)
set_target_properties(DetourCrowd PROPERTIES DEBUG_POSTFIX -d)

set(DetourCrowd_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")

target_include_directories(DetourCrowd PUBLIC
    "$<BUILD_INTERFACE:${DetourCrowd_INCLUDE_DIR}>"
)

target_link_libraries(DetourCrowd
    Detour
)

set_target_properties(DetourCrowd PROPERTIES
        SOVERSION ${SOVERSION}
        VERSION ${LIB_VERSION}
        COMPILE_PDB_OUTPUT_DIRECTORY .
        COMPILE_PDB_NAME "DetourCrowd-d"
        )

install(TARGETS DetourCrowd
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT library
        )

install(FILES ${INCLUDES} DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/recastnavigation)
if(MSVC)
    install(FILES "$<TARGET_FILE_DIR:DetourCrowd>/DetourCrowd-d.pdb" CONFIGURATIONS "Debug" DESTINATION "lib")
endif()
