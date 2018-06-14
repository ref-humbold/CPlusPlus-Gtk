cmake_minimum_required(VERSION 3.5)

# PROJECT
project(generator_pi VERSION 1.0)
set(PROJECT_DIR ${CMAKE_BINARY_DIR}/..)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# COMPILER
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# OUTPUT
add_executable(generator_pi generator_pi.cpp)
target_link_libraries(generator_pi ${GTKMM_LIBRARIES})
