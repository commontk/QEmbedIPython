
#------------------------------------------------------------------------------
# Dependencies
#------------------------------------------------------------------------------
include(${QT_USE_FILE})

find_package(PythonLibs REQUIRED)

find_package(CTK REQUIRED)

#-----------------------------------------------------------------------------
# Update CMake module path
#-----------------------------------------------------------------------------
set(CMAKE_MODULE_PATH
  ${CTK_CMAKE_DIR}
  ${CMAKE_MODULE_PATH}
  )
  
#------------------------------------------------------------------------------
find_package(PythonInterp REQUIRED)
# Extract python lib path
get_filename_component(PYTHON_DIR_PATH ${PYTHON_EXECUTABLE} PATH)
set(PYTHON_LIBRARY_PATH ${PYTHON_DIR_PATH}/../lib)
if(WIN32)
  set(PYTHON_LIBRARY_PATH ${PYTHON_DIR_PATH})
endif()

ctkMacroSetPaths("${PYTHON_LIBRARY_PATH}")
execute_process(
  COMMAND ${PYTHON_EXECUTABLE} -c "import sys; print sys.version[:3]"
  OUTPUT_VARIABLE Slicer_PYTHON_VERSION_DOT
  OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX REPLACE "[.]" "" Slicer_PYTHON_VERSION ${Slicer_PYTHON_VERSION_DOT})
message(STATUS "Configuring ${SlicerApp_APPLICATION_NAME} with python ${Slicer_PYTHON_VERSION_DOT}")

#------------------------------------------------------------------------------
# Include directories
#------------------------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR 1)

include_directories(
  ${PYTHON_INCLUDE_DIRS}
  ${CTK_INCLUDE_DIRS}
  )

#------------------------------------------------------------------------------
# Build libary
#------------------------------------------------------------------------------
set(KIT ${PROJECT_NAME}Lib)

set(KIT_SRCS
  qEmbedIPythonPythonManager.h
  qEmbedIPythonPythonManager.cxx
  )
set(KIT_MOC_SRCS
  qEmbedIPythonPythonManager.h
  )
QT4_WRAP_CPP(KIT_SRCS ${KIT_MOC_SRCS})

add_library(${KIT} SHARED
  ${KIT_SRCS}
  )
target_link_libraries(${KIT}
  ${CTK_LIBRARIES}
  ${PYTHON_LIBRARIES}
  ${QT_LIBRARIES}
  )

generate_export_header(${KIT})

#------------------------------------------------------------------------------
# Build executable
#------------------------------------------------------------------------------
set(KIT ${PROJECT_NAME}-real)
add_executable(${KIT} "${PROJECT_NAME}.cxx")
target_link_libraries(${KIT}
  ${PROJECT_NAME}Lib
  )

#------------------------------------------------------------------------------
# Configure launcher
#------------------------------------------------------------------------------
include(${CTKAPPLAUNCHER_DIR}/CMake/ctkAppLauncher.cmake)

# LIBRARY_PATHS
set(${PROJECT_NAME}_LIBRARY_PATHS_BUILD
  <APPLAUNCHER_DIR>/bin/<CMAKE_CFG_INTDIR>
  ${CTK_DIR}/CTK-build/bin/<CMAKE_CFG_INTDIR>
  ${OPENSSL_EXPORT_LIBRARY_DIR}
  ${QT_LIBRARY_DIR}
  )
if(NOT Slicer_USE_SYSTEM_python)
  list(APPEND ${PROJECT_NAME}_LIBRARY_PATHS_BUILD
    ${PYTHON_LIBRARY_PATH}
    )
endif()

set(pythonpath_subdir lib/python${Slicer_PYTHON_VERSION_DOT})
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(pythonpath_subdir Lib)
endif()

# XXX Launcher should be configured using settings set in external projects
set(python_DIR ${CMAKE_BINARY_DIR}/../python-install)

# PATHS
set(${PROJECT_NAME}_PATHS_BUILD
  ${QT_BINARY_DIR}
  ${python_DIR}/bin
  )

# ENVVARS
if(NOT Slicer_USE_SYSTEM_python)
  set(PYTHONHOME ${CMAKE_BINARY_DIR}/../python-install)
  list(APPEND ${PROJECT_NAME}_ENVVARS_BUILD "PYTHONHOME=${PYTHONHOME}")
  list(APPEND ${PROJECT_NAME}_ADDITIONAL_PATH_ENVVARS_BUILD "PYTHONPATH")
endif()
set(${PROJECT_NAME}_PYTHONPATH_BUILD
  )
if(NOT ${PROJECT_NAME}_USE_SYSTEM_python)
  list(APPEND ${PROJECT_NAME}_PYTHONPATH_BUILD
    "${PYTHONHOME}/${pythonpath_subdir}"
    "${PYTHONHOME}/${pythonpath_subdir}/lib-dynload"
    "${PYTHONHOME}/${pythonpath_subdir}/site-packages"
    # XXX Support dev mode
    "${CMAKE_BINARY_DIR}/../IPython/src/traitlets"
    "${CMAKE_BINARY_DIR}/../IPython"
    )
endif()

ctkAppLauncherConfigure(
  TARGET "${PROJECT_NAME}-real"
  APPLICATION_NAME "${PROJECT_NAME}"
  DESTINATION_DIR "${CMAKE_BINARY_DIR}"
  LIBRARY_PATHS_BUILD "${${PROJECT_NAME}_LIBRARY_PATHS_BUILD}"
  PATHS_BUILD "${${PROJECT_NAME}_PATHS_BUILD}"
  ENVVARS_BUILD "${${PROJECT_NAME}_ENVVARS_BUILD}"
  ADDITIONAL_PATH_ENVVARS_BUILD ${${PROJECT_NAME}_ADDITIONAL_PATH_ENVVARS_BUILD}
  ADDITIONAL_PATH_ENVVARS_PREFIX ${PROJECT_NAME}_
  )

set(QEmbedIPython_LAUNCHER_EXECUTABLE ${QEmbedIPython_BINARY_DIR}/../python-install/bin/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX})
set(QEmbedIPython_LAUNCH_COMMAND ${QEmbedIPython_LAUNCHER_EXECUTABLE} --launcher-no-splash --launch)

add_custom_target(StartIPythonServer
  COMMAND ${QEmbedIPython_LAUNCH_COMMAND} ipython notebook --NotebookApp.kernel_manager_class=existingkernel.managers.ExistingMappingKernelManager
  COMMENT "Starting IPython server"
  )
