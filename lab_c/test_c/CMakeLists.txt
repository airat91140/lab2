cmake_minimum_required(VERSION 3.17)
project(Test_с)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(test/googletest)
include_directories(test/googletest/googletest/include)

add_executable(test_c
        test.cpp)

target_link_libraries(test_c gtest gtest_main)

TARGET_LINK_LIBRARIES( test_c X16c )
