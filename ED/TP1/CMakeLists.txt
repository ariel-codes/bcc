cmake_minimum_required(VERSION 3.17)
project(TP1)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(TP1
        src/Main.cc
        src/Base.cc
        src/Map.cc
        src/Robot.cc
        src/QuadTree.cc
        )
