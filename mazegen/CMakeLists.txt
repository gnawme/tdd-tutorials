cmake_minimum_required(VERSION 3.6)
project(mazegen)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp RBMaze.cpp RBMaze.hpp)
add_executable(mazegen ${SOURCE_FILES})