cmake_minimum_required(VERSION 3.17)
project(lab2_b)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_executable(lab2_b
        functions.cpp
        functions.h
        main.cpp
)

include_directories(lib)

TARGET_LINK_LIBRARIES( lab2_b
        X16 )

add_subdirectory(Test_b)