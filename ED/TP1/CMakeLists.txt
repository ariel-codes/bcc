cmake_minimum_required (VERSION 3.17)
project (TP1)

set (CMAKE_CXX_STANDARD 11)

include_directories (include)

add_executable (TP1
    src/Main.cc
    Makefile src/QuadTree.cpp include/QuadTree.hpp src/parsers.cpp src/Map.cpp include/Map.hpp src/Robot.cpp include/Robot.hpp src/Base.cpp include/Base.hpp src/Queue.cpp include/Queue.hpp)
