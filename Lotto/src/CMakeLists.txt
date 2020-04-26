cmake_minimum_required(VERSION 3.10)

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
set(SOURCES
    ../lotto.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}")
add_executable(lotto ${SOURCES})
target_link_libraries(lotto ${GTKMM_LIBRARIES})
