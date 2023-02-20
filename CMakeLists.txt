cmake_minimum_required(VERSION 3.14)
project(IhorGUI
    VERSION 1.0.0
    DESCRIPTION "GUI library for coursework"
    LANGUAGES CXX)

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(IHORGUI_INSTALL "Generate target for installing IhorGUI" ${is_top_level})
set_if_undefined(IHORGUI_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/IhorGUI" CACHE STRING
    "Install path for IhorGUI package-related CMake files")

add_library(IhorGUI)
add_library(IhorGUI::IhorGUI ALIAS IhorGUI)

# IhorGUI sources

include(GenerateExportHeader)

set(sources
    include/IhorGUI/IhorGUI.h
    src/IhorGUI.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

# IhorGUI dependencies

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(IhorGUI ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY})

# IhorGUI target

include(CMakePackageConfigHelpers)

target_sources(IhorGUI PRIVATE ${sources})
target_compile_definitions(IhorGUI PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:IHORGUI_STATIC_DEFINE>")

target_include_directories(IhorGUI
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(IhorGUI PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(IHORGUI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/ihorgui-config.cmake.in ihorgui-config.cmake
        INSTALL_DESTINATION "${IHORGUI_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(ihorgui-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS IhorGUI EXPORT IhorGUI_export
        RUNTIME COMPONENT IhorGUI
        LIBRARY COMPONENT IhorGUI NAMELINK_COMPONENT IhorGUI-dev
        ARCHIVE COMPONENT IhorGUI-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT IhorGUI-dev)

    set(targets_file "ihorgui-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "ihorgui-static-targets.cmake")
    endif()

    install(EXPORT IhorGUI_export
        COMPONENT IhorGUI-dev
        FILE "${targets_file}"
        DESTINATION "${IHORGUI_INSTALL_CMAKEDIR}"
        NAMESPACE IhorGUI::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/ihorgui-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/ihorgui-config-version.cmake"
        COMPONENT IhorGUI-dev
        DESTINATION "${IHORGUI_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:IhorGUI>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:IhorGUI>/$<TARGET_FILE_PREFIX:IhorGUI>$<TARGET_FILE_BASE_NAME:IhorGUI>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT IhorGUI-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()
