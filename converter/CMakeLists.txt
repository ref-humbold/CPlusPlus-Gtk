cmake_minimum_required(VERSION 3.5)

# PROJECT
project(converter VERSION 1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# SOURCES
set(SOURCES "converter.cpp")

# COMPILER
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# OUTPUT
add_executable(converter ${SOURCES})
