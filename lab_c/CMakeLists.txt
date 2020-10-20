cmake_minimum_required(VERSION 3.17)
project(lab2_c)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
include_directories(lib)

add_executable(lab2_c
        functions.cpp
        functions.h
        main.cpp
)

TARGET_LINK_LIBRARIES( lab2_c
        X16 )

add_subdirectory(test_c)