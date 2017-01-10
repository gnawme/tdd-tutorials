cmake_minimum_required(VERSION 3.6)
project(slinky)

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES SlinkyTest.cpp Slinky.hpp)
add_executable(slinky ${SOURCE_FILES})
target_link_libraries(slinky -lgtest pthread)
