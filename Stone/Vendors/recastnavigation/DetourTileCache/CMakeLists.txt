file(GLOB SOURCES Source/*.cpp)
file(GLOB INCLUDES Include/*.h)

add_library(DetourTileCache ${SOURCES} ${INCLUDES})

add_library(RecastNavigation::DetourTileCache ALIAS DetourTileCache)
set_target_properties(DetourTileCache PROPERTIES DEBUG_POSTFIX -d)

set(DetourTileCache_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")

target_include_directories(DetourTileCache PUBLIC
    "$<BUILD_INTERFACE:${DetourTileCache_INCLUDE_DIR}>"
)

target_link_libraries(DetourTileCache
    Detour
)

set_target_properties(DetourTileCache PROPERTIES
        SOVERSION ${SOVERSION}
        VERSION ${LIB_VERSION}
        COMPILE_PDB_OUTPUT_DIRECTORY .
        COMPILE_PDB_NAME "DetourTileCache-d"
        )


install(TARGETS DetourTileCache
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT library
        )

install(FILES ${INCLUDES} DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/recastnavigation)
if(MSVC)
    install(FILES "$<TARGET_FILE_DIR:DetourTileCache>/DetourTileCache-d.pdb" CONFIGURATIONS "Debug" DESTINATION "lib")
endif()
