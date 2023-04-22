cmake_minimum_required(VERSION 3.25)
project(tjs2json CXX)

set(CMAKE_CXX_STANDARD 17)


add_library(Lexical_Analysis STATIC Lexical_Tokens.cpp Lexical_Tokens.h Keyword_Symbols.h TJS_Data_Types.cpp TJS_Data_Types.h)

# Test

add_executable(test test.cpp)