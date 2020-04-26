cmake_minimum_required(VERSION 3.10)
project(Converter VERSION 0.3.190612)

# PROPERTIES
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(EXE_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin")

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
include_directories("${INCLUDE_DIR}")

# OUTPUT
add_subdirectory("${SRC_DIR}")
