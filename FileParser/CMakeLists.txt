cmake_minimum_required(VERSION 3.20)
project(FileParser)

set(CMAKE_CXX_STANDARD 11)

add_executable(FileParser main.cpp FileParser.cpp FileParser.h nnLayer.cpp nnLayer.h globals.h)
