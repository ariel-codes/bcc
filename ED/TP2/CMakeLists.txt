cmake_minimum_required (VERSION 3.17)
project (TP2)

set (CMAKE_CXX_STANDARD 11)

include_directories (include)

add_executable (
    TP2
    src/Main.cpp
    src/BaseDistancia.cpp
    src/Array.cpp
    src/insertionsort.cpp src/mergesort.cpp src/quicksort.cpp)
