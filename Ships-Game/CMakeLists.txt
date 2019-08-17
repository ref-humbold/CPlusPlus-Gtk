cmake_minimum_required(VERSION 3.5)
project(Ships-Game VERSION 0.3.190423)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# SOURCES
set(SOURCES ships_game.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(ships_game ${SOURCES})
