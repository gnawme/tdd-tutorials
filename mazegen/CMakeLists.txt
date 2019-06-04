cmake_minimum_required(VERSION 3.5)
project(mazegen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(SOURCE_FILES main.cpp RBMaze.cpp RBMaze.hpp)
add_executable(mazegen ${SOURCE_FILES})