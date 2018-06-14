cmake_minimum_required(VERSION 3.5.1)
project(converter)

set(PROJECT_DIR ${CMAKE_BINARY_DIR}/..)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

add_executable(converter converter.cpp)
