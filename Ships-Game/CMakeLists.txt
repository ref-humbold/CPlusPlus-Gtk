cmake_minimum_required(VERSION 3.10)
project(Ships-Game VERSION 0.3.190423)

# PROPERTIES
set(EXE_NAME ships_game)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(EXE_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin")

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# SOURCES
include_directories(${INCLUDE_DIR})

# OUTPUT
add_subdirectory(${SRC_DIR})
