cmake_minimum_required(VERSION 3.27)
project(lab1_tema)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_tema App.cpp
        VectorDinamic.cpp
        VectorDinamic.h
        IteratorVectorDinamic.cpp
        IteratorVectorDinamic.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
