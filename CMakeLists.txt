
cmake_minimum_required(VERSION 2.8.9)

project(QEmbedIPython)

#-----------------------------------------------------------------------------
# Superbuild
#------------------------------------------------------------------------------
set(${PROJECT_NAME}_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(CMAKE_MODULE_PATH "${${PROJECT_NAME}_CMAKE_DIR}" ${CMAKE_MODULE_PATH})
set(EXTERNAL_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Externals)
set(EXTERNAL_PROJECT_FILE_PREFIX "External_")
include(ExternalProject)
include(ExternalProjectDependency)

#------------------------------------------------------------------------------
include(ListToString)
include(GenerateExportHeader)
include(SlicerMacroGetOperatingSystemArchitectureBitness)

#------------------------------------------------------------------------------
# Options
#------------------------------------------------------------------------------
option(${CMAKE_PROJECT_NAME}_USE_GIT_PROTOCOL "If behind a firewall turn this off to use https instead." ON)
set(git_protocol "git")
if(NOT ${CMAKE_PROJECT_NAME}_USE_GIT_PROTOCOL)
  set(git_protocol "https")
endif()

#-----------------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------------
find_package(Qt4 REQUIRED)
mark_as_superbuild(VARS QT_QMAKE_EXECUTABLE LABELS "FIND_PACKAGE")

set(PYTHON_ENABLE_SSL 1)

#------------------------------------------------------------------------------
# Configure and build top-level project
#------------------------------------------------------------------------------
option(${PROJECT_NAME}_SUPERBUILD "Build ${PROJECT_NAME} and the projects it depends on." ON)
mark_as_advanced(${PROJECT_NAME}_SUPERBUILD)
if(${PROJECT_NAME}_SUPERBUILD)
  set(${PROJECT_NAME}_DEPENDENCIES CTK IPython)
  ExternalProject_Include_Dependencies(${PROJECT_NAME} DEPENDS_VAR ${PROJECT_NAME}_DEPENDENCIES)
  ExternalProject_Add(${PROJECT_NAME}
    ${${PROJECT_NAME}_EP_ARGS}
    DOWNLOAD_COMMAND ""
    INSTALL_COMMAND ""
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-build
    CMAKE_CACHE_ARGS
      ${EMSCRIPTEN_TOOLCHAIN_OPTIONS}
      -D${PROJECT_NAME}_SUPERBUILD:BOOL=OFF
      -D${PROJECT_NAME}_SUPERBUILD_BINARY_DIR:PATH=${${PROJECT_NAME}_BINARY_DIR}
    DEPENDS
      ${${PROJECT_NAME}_DEPENDENCIES}
    )
  return()
endif()

#------------------------------------------------------------------------------
# Output directories
#------------------------------------------------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#------------------------------------------------------------------------------
# Inner-build
#------------------------------------------------------------------------------

add_subdirectory(src)
