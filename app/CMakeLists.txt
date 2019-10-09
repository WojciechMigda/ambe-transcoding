add_executable( ambep2 "src/dummy.cpp" )
target_sources( ambep2 PRIVATE "src/main.cpp" )

find_package( ApcoP2 )

#target_link_libraries( FreeCalculator
#    PRIVATE MyCalc::basicmath
#            Boost::program_options )

