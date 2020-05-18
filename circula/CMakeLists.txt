cmake_minimum_required(VERSION 3.5)
project(circula)

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(
    SOURCE_FILES
    CirculaTest.cpp
    Circula.h
)

add_executable(circula ${SOURCE_FILES})
target_link_libraries(circula -lgtest pthread)
