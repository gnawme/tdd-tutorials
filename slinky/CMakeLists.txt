cmake_minimum_required(VERSION 3.5)
project(slinky)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES SlinkyTest.cpp Slinky.h)
add_executable(slinky ${SOURCE_FILES})
target_link_libraries(slinky -lgtest pthread)
