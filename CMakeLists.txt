cmake_minimum_required(VERSION 3.13)
project(hex)

set(CMAKE_CXX_STANDARD 14)

add_executable(hex main.cpp HexLexer.h HexLexer.cpp)