cmake_minimum_required(VERSION 3.17)
project(TP1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)

add_executable(tp02
        src/Main.cc
        src/Entrada.cc src/Vertice.cc include/Vertice.h src/AlgoritmoTarjanMod.cc include/AlgoritmoTarjanMod.h src/ComponenteFConectado.cc include/ComponenteFConectado.h)
