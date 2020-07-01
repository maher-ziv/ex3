cmake_minimum_required(VERSION 3.17.2)

project(partC)
set (CMAKE_CXX_STANDARD 11)
set(MTM_FLAGS "-std=c++11 -Wall -Werror -pedantic-errors -g")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS} -DNDEBUG")
set(CMAKE_CXX_FLAG ${MTM_FLAGS})

include_directories(. ./tests)
set(HEADER_FILES Game.h Character.h  Medic.h Sniper.h Soldier.h Auxiliaries.h Exceptions.h )
set(SRC_FILES Game.cpp Character.cpp  Medic.cpp Sniper.cpp Soldier.cpp Auxiliaries.cpp)
add_executable(partC  ${HEADER_FILES} ${SRC_FILES} tests/test_partC.cpp)
#add_executable(partC  ${HEADER_FILES} ${SRC_FILES} )

