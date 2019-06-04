cmake_minimum_required(VERSION 3.5)
project(beastie)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES BeastieTest.cpp Beastie.hpp)
add_executable(beastie ${SOURCE_FILES})
target_link_libraries(beastie -lgtest pthread)
