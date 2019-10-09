add_executable( ambep2 "src/dummy.cpp" )
target_sources( ambep2 PRIVATE "src/main.cpp" )

find_package( ApcoP2 )

target_link_libraries( ambep2 PRIVATE ${ApcoP2_LIBRARIES} )
target_include_directories( ambep2 PRIVATE ${ApcoP2_INCLUDE_DIR} )
