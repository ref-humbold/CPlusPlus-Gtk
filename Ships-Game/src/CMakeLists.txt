cmake_minimum_required(VERSION 3.10)

# SOURCES
set(SOURCES
    ../ships_game.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}")
add_executable(ships_game ${SOURCES})
