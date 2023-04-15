cmake_minimum_required(VERSION 3.10)
project(Lotto VERSION 0.2.190612)

# PROPERTIES
set(CMD_EXE_NAME lotto)
set(GTK_EXE_NAME lotto-gtk)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/buildOut")
set(EXE_OUTPUT_DIR "${OUTPUT_DIR}/bin")
set(LIB_OUTPUT_DIR "${OUTPUT_DIR}/dist")
set(DOCS_OUTPUT_DIR "${OUTPUT_DIR}/docs")

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# SOURCES
include_directories(${INCLUDE_DIR})

# OUTPUT
add_subdirectory(${SRC_DIR})
