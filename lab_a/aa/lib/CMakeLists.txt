cmake_minimum_required(VERSION 3.17)
project(static)
set(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY( X16 STATIC
        X16.h
        X16.cpp)