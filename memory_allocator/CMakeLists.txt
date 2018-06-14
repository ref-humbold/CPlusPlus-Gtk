cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE Release)

# PROJECT
project(memalc VERSION 1.0)
set(PROJECT_DIR ${CMAKE_BINARY_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

# PACKAGES
find_package(Threads REQUIRED)

# COMPILER
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -fPIC")
set(CMAKE_USE_PTHREADS_INIT true)
set(CMAKE_USE_PTHREADS_INIT ON)

# OUTPUT
add_library(memalc SHARED memalc.c)
target_link_libraries(memalc Threads::Threads)
