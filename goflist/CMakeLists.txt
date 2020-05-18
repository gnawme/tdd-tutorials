cmake_minimum_required(VERSION 3.5)
project(goflist)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS} ../slinky)

set(SOURCE_FILES GoFListTest.cpp GoFList.hpp GoFIterator.hpp GoFListIterator.hpp)
add_executable(goflist ${SOURCE_FILES})
target_link_libraries(goflist -lgtest pthread)

