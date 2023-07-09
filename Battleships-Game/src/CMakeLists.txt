cmake_minimum_required(VERSION 3.10)

# SOURCES
set(SOURCES "../battleships_game.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXE_OUTPUT_DIR})
add_executable(${EXE_NAME} ${SOURCES})
