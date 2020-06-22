cmake_minimum_required(VERSION 3.17.2)

project(partA)
set (CMAKE_CXX_STANDARD 11)
set(MTM_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors -g")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS} -DNDEBUG")

set(CMAKE_CXX_FLAG ${MTM_FLAGS})

add_executable(partA IntMatrix.cpp Auxiliaries.cpp ./tests/partA_tester.cpp)

