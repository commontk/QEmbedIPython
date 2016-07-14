set(proj existingkernel)

# Set dependency list
set(${proj}_DEPENDENCIES python IPython python-pip)

# Include dependent projects if any
ExternalProject_Include_Dependencies(${proj} PROJECT_VAR proj DEPENDS_VAR ${proj}_DEPENDENCIES)

if(${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj})
  # XXX - Add a test checking if <proj> is available
endif()

if(NOT DEFINED ${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj})
  set(${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj} ${${CMAKE_PROJECT_NAME}_USE_SYSTEM_python})
endif()

if(NOT ${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj})

  ExternalProject_Add(${proj}
    ${${proj}_EP_ARGS}
    GIT_REPOSITORY "${git_protocol}://github.com/jcfr/existingkernel.git"
    GIT_TAG "433408bc3d5a4494b635feb50b8d5d8af3f001cf"
    SOURCE_DIR ${proj}
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${PYTHON_EXECUTABLE} setup.py develop --prefix=${python_DIR}
    DEPENDS
      ${${proj}_DEPENDENCIES}
    )

  set(_EP_${proj}_SETUPTOOLS_LOCK 1)

else()
  ExternalProject_Add_Empty(${proj} DEPENDS ${${proj}_DEPENDENCIES})
endif()
