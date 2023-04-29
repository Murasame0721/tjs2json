cmake_minimum_required(VERSION 3.25)
project(tjs2json CXX)

set(CMAKE_CXX_STANDARD 17)


add_library(Lexical_Analysis TjsToken.cpp TjsToken.h TjsLexicalAnalyzer.cpp TjsLexicalAnalyzer.h)

# Test

add_executable(test test.cpp)
