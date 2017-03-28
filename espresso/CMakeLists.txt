cmake_minimum_required(VERSION 3.6)
project(espresso)

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES EspressoTest.cpp Espresso.hpp Espresso.cpp)
add_executable(espresso ${SOURCE_FILES})

target_link_libraries(espresso -lgtest pthread)
