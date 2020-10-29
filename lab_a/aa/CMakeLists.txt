cmake_minimum_required(VERSION 3.17)
project(lab2_a)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_executable(lab2_a
        functions.cpp
        functions.h
        main.cpp
)

include_directories(lib)

TARGET_LINK_LIBRARIES( lab2_a
        X16 )

add_subdirectory(Test_a)