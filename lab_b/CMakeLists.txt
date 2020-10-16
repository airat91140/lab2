cmake_minimum_required(VERSION 3.17)
project(lab2_b)

set(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY( X16b STATIC
        X16.cpp
        X16.h)

include_directories(.)

SET( APP_EXE X16 )

add_executable(${APP_EXE}
        functions.cpp
        functions.h
        main.cpp
)

TARGET_LINK_LIBRARIES( ${APP_EXE}
        X16b )

add_subdirectory(Test_b)