cmake_minimum_required(VERSION 3.6)
project(bowling_game)
find_library(GTest required)
include_directories(${GTEST_INCLUDE_DIRS})


set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES BowlingGameTest.cpp BowlingGameTest.h BowlingGame.h)

add_executable(bowling_game ${SOURCE_FILES})
target_link_libraries(bowling_game -lgtest pthread)
