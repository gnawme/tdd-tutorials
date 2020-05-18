cmake_minimum_required(VERSION 3.5)
project(miscellar)

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wno-write-strings")

set(SOURCE_FILES main.cpp)
add_executable(miscellar ${SOURCE_FILES})

target_link_libraries(miscellar -lgtest pthread)
