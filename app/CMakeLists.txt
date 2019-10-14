set( CMAKE_CXX_STANDARD 17 )

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable( ambep2 "src/dummy.cpp" )
target_sources( ambep2 PRIVATE "src/main.cpp" )

find_package( ApcoP2 REQUIRED )
find_package( nlohmann_json 3.2.0 REQUIRED )

target_link_libraries( ambep2 PRIVATE ${ApcoP2_LIBRARIES} )
target_include_directories( ambep2 PRIVATE ${ApcoP2_INCLUDE_DIR} ${nlohmann_json_INCLUDE_DIR} )
