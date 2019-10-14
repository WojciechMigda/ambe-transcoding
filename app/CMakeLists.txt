set( CMAKE_CXX_STANDARD 17 )

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package( ApcoP2 REQUIRED )
find_package( nlohmann_json 3.2.0 REQUIRED )

add_executable( ambep2_enc "src/dummy.cpp" )
target_sources( ambep2_enc PRIVATE "src/encode.cpp" )

target_link_libraries( ambep2_enc PRIVATE ${ApcoP2_LIBRARIES} )
target_include_directories( ambep2_enc PRIVATE ${ApcoP2_INCLUDE_DIR} ${nlohmann_json_INCLUDE_DIR} )
target_compile_options( ambep2_enc PRIVATE "-Wno-psabi" )


add_executable( ambep2_dec "src/dummy.cpp" )
target_sources( ambep2_dec PRIVATE "src/decode.cpp" )

target_link_libraries( ambep2_dec PRIVATE ${ApcoP2_LIBRARIES} )
target_include_directories( ambep2_dec PRIVATE ${ApcoP2_INCLUDE_DIR} ${nlohmann_json_INCLUDE_DIR} )
target_compile_options( ambep2_dec PRIVATE "-Wno-psabi" )
