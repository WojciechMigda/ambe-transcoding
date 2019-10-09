# FindApcoP2
# ----------
#
# Try to find ApcoP2
#
# Once done this will define:
#
# ::
#
#   ApcoP2_FOUND        - system has ApcoP2
#   ApcoP2_INCLUDE_DIR  - include paths to use ApcoP2
#   ApcoP2_LIBRARIES    - Link these to use ApcoP2

set(ApcoP2_FOUND 0)
if( UNIX )
  find_path( ApcoP2_INCLUDE_DIR
    NAMES apcop2.h
    PATHS ${PROJECT_SOURCE_DIR}/dvsi/include
    NO_CMAKE_FIND_ROOT_PATH
    )

  find_library( ApcoP2_LIBRARIES
    libapcop2.a
    ${PROJECT_SOURCE_DIR}/dvsi/lib
    NO_CMAKE_FIND_ROOT_PATH
    )

endif()

include( ${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake )
find_package_handle_standard_args( ApcoP2 DEFAULT_MSG ApcoP2_LIBRARIES ApcoP2_INCLUDE_DIR )

mark_as_advanced(
  ApcoP2_INCLUDE_DIR
  ApcoP2_LIBRARIES
)
