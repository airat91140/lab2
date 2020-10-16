cmake_minimum_required(VERSION 3.17)
project(Test_a)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(test/googletest)
include_directories(test/googletest/googletest/include)

add_executable(Test_a
        test.cpp)

target_link_libraries(Test_a gtest gtest_main)

TARGET_LINK_LIBRARIES( Test_a X16a )
