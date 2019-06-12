cmake_minimum_required(VERSION 3.5)
project(lotto VERSION 0.2.190612)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
include_directories("${PROJECT_SOURCE_DIR}/include")
set(SOURCES "lotto.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_executable(lotto ${SOURCES})
target_link_libraries(lotto ${GTKMM_LIBRARIES})
