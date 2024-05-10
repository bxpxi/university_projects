cmake_minimum_required(VERSION 3.22)
project(lab8_bun)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

add_executable(lab8_bun main.cpp
        domain.cpp
        domain.h
        cos.cpp
        cos.h
        repo.cpp
        repo.h
        validator.cpp
        validator.h
        service.cpp
        service.h
        consola.cpp
        consola.h
        teste.cpp
        teste.h
        undo.h)
