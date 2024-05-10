cmake_minimum_required(VERSION 3.22)
project(lab7_bun)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab7_bun main.cpp
        domain.cpp
        domain.h
        VectorDinamic.h
        repository.cpp
        repository.h
        validators.h
        service.cpp
        service.h
        ui.cpp
        ui.h)
