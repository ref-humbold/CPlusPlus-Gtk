cmake_minimum_required(VERSION 3.5.1)
project(traceroute)

set(PROJECT_DIR ${CMAKE_BINARY_DIR}/..)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_DIR})

include_directories(${PROJECT_DIR})
file(GLOB SOURCES "${PROJECT_DIR}/*.cpp")

add_executable(traceroute ${SOURCES})
