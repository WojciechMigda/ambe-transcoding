# Findnlohmann_json
# ----------
#
# Try to find nlohmann_json
#
# Once done this will define:
#
# ::
#
#   nlohmann_json_FOUND        - system has nlohmann_json
#   nlohmann_json_INCLUDE_DIR  - include paths to use nlohmann_json

set(nlohmann_json_FOUND 0)
if( UNIX )
  find_path( nlohmann_json_INCLUDE_DIR
    NAMES json/json.hpp
    PATHS ${PROJECT_SOURCE_DIR}/nlohmann
    NO_CMAKE_FIND_ROOT_PATH
    )
endif()

include( ${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake )
find_package_handle_standard_args( nlohmann_json DEFAULT_MSG nlohmann_json_INCLUDE_DIR )

mark_as_advanced(
    nlohmann_json_INCLUDE_DIR
)
