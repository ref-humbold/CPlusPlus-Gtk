cmake_minimum_required(VERSION 3.5)

# PROJECT
project(traceroute VERSION 1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# SOURCES
include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# COMPILER
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# OUTPUT
add_executable(traceroute ${SOURCES})
