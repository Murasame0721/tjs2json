cmake_minimum_required(VERSION 3.25)
project(tjs2json CXX)

set(CMAKE_CXX_STANDARD 20)


add_library(Lexical_Analysis TjsToken.h)

# Test

add_executable(test test.cpp)
