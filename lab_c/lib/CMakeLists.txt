cmake_minimum_required(VERSION 3.17)
project(lib)

set(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY( X16 STATIC
        X16.cpp
        X16.h)
