cmake_minimum_required(VERSION 3.5)

# PROJECT
project(lotto VERSION 1.0)
set(PROJECT_DIR ${CMAKE_BINARY_DIR}/..)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

# COMPILER
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# OUTPUT
add_executable(lotto lotto.cpp)
