cmake_minimum_required(VERSION 3.6)
project(miscellar)

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wno-write-strings")
set(SOURCE_FILES main.cpp)
add_executable(miscellar ${SOURCE_FILES})

target_link_libraries(miscellar -lgtest pthread)
