cmake_minimum_required(VERSION 3.6)
project(soundex)
find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES SoundexTest.cpp Soundex.h)
add_executable(soundex ${SOURCE_FILES})
target_link_libraries(soundex -lgtest pthread)
