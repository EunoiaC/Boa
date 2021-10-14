cmake_minimum_required(VERSION 3.20)
project(Boa)

set(CMAKE_CXX_STANDARD 14)

add_executable(Boa main.cpp Includes/Value.cpp Includes/Value.h Includes/Lexer.cpp Includes/Lexer.h)
