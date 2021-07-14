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

add_executable(tp01
        src/Main.cc
        src/Posto.cc
        src/Pessoa.cc
        src/Participante.cc
        src/Localizacao.cc
        src/Emparelhador.cc
        src/entrada.cc)
