cmake_minimum_required(VERSION 3.5)
project(PI-Generator VERSION 0.4.190612)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
include_directories(include)
set(SOURCES
    src/gtk_app.cpp
    src/pi_generator.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(pi_generator ${SOURCES})
target_link_libraries(pi_generator ${GTKMM_LIBRARIES})
