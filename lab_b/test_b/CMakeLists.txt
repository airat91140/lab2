cmake_minimum_required(VERSION 3.17)
project(Test_b)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(test/googletest)
include_directories(test/googletest/googletest/include)

add_executable(Test_b
        test.cpp)

target_link_libraries(Test_b gtest gtest_main)

TARGET_LINK_LIBRARIES( Test_b X16b )
