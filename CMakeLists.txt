cmake_minimum_required(VERSION 3.20)
project(mp2_lab2_matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(gtest)
include_directories(include)

add_executable(mp2_lab2_matrix
        gtest/gtest-all.cc
        gtest/gtest.h
        include/utmatrix.h
        samples/sample_matrix.cpp
        test/test_main.cpp
        test/test_tmatrix.cpp
        test/test_tvector.cpp)
