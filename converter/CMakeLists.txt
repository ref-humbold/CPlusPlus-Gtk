cmake_minimum_required(VERSION 3.5)
project(converter VERSION 1.1)

# COMPILER
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# SOURCES
set(SOURCES "converter.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_executable(converter ${SOURCES})
