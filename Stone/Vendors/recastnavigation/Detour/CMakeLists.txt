file(GLOB SOURCES Source/*.cpp)
file(GLOB INCLUDES Include/*.h)
add_library(Detour ${SOURCES} ${INCLUDES})

add_library(RecastNavigation::Detour ALIAS Detour)
set_target_properties(Detour PROPERTIES DEBUG_POSTFIX -d)

set(Detour_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")

target_include_directories(Detour PUBLIC
    "$<BUILD_INTERFACE:${Detour_INCLUDE_DIR}>"
)

set_target_properties(Detour PROPERTIES
        SOVERSION ${SOVERSION}
        VERSION ${LIB_VERSION}
        COMPILE_PDB_OUTPUT_DIRECTORY .
        COMPILE_PDB_NAME "Detour-d"
        )

install(TARGETS Detour
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT library
        )

install(FILES ${INCLUDES} DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}/recastnavigation)
if(MSVC)
    install(FILES "$<TARGET_FILE_DIR:Detour>/Detour-d.pdb" CONFIGURATIONS "Debug" DESTINATION "lib")
endif()
