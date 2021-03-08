cmake_minimum_required (VERSION 3.17)
project (TP2)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -O3")
set (BENCHMARK_DOWNLOAD_DEPENDENCIES true)
set (CMAKE_BUILD_TYPE Release)

include_directories (include)

add_subdirectory (benchmark)

add_executable (
    TP2Benchmark
    test/Benchmark.cpp
    src/BaseDistancia.cpp
    src/Array.cpp
    src/insertionsort.cpp
    src/mergesort.cpp
    src/quicksort.cpp
    src/cyclesort.cpp)

add_executable (
    TP2Test
    test/Test.cpp
    src/BaseDistancia.cpp
    src/Array.cpp
    src/insertionsort.cpp
    src/mergesort.cpp
    src/quicksort.cpp
    src/cyclesort.cpp)

target_link_libraries (TP2Benchmark benchmark::benchmark)
