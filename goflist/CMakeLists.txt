cmake_minimum_required(VERSION 3.6)
project(goflist)

set(CMAKE_CXX_STANDARD 14)
find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS} ../slinky)

set(SOURCE_FILES GoFListTest.cpp GoFList.hpp GoFIterator.hpp GoFListIterator.hpp)
add_executable(goflist ${SOURCE_FILES})
target_link_libraries(goflist -lgtest pthread)

