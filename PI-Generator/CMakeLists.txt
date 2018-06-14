cmake_minimum_required(VERSION 3.5.1)
project(generator_pi)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

set(PROJECT_DIR ${CMAKE_BINARY_DIR}/..)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

add_executable(generator_pi generator_pi.cpp)
target_link_libraries(generator_pi ${GTKMM_LIBRARIES})
