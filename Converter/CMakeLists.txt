cmake_minimum_required(VERSION 3.10)
project(Converter VERSION 0.4.201229)

# PROPERTIES
set(CMD_EXE_NAME converter)
set(GTK_EXE_NAME converter-gtk)
set(LIB_NAME converter-lib)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/buildOut")
set(EXE_OUTPUT_DIR "${OUTPUT_DIR}/bin")
set(TEST_EXE_OUTPUT_DIR "${OUTPUT_DIR}/test")
set(LIB_OUTPUT_DIR "${OUTPUT_DIR}/dist")

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# PACKAGES
find_package(GTest)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
include_directories(${INCLUDE_DIR})

# OUTPUT
add_subdirectory(${SRC_DIR})

if(GTEST_FOUND)
    message(STATUS "GTest found")
    include(CTest)
    add_subdirectory(${TEST_DIR})
else()
    message(WARNING "GTest not found - skipping tests")
endif()
