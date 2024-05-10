cmake_minimum_required(VERSION 3.27)
project(lab6_var2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab6_var2 main.cpp
        domain.cpp
        domain.h
        repository.cpp
        repository.h
        service.cpp
        service.h
        ui.cpp
        ui.h
        tests.cpp
        tests.h)
