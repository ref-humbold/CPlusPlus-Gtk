cmake_minimum_required(VERSION 3.5)
set(CMAKE_BUILD_TYPE Release)

# PROJECT
project(memalc VERSION 1.0)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

# PACKAGES
set(CMAKE_THREAD_PREFER_PTHREAD true)
set(THREADS_PREFER_PTHREAD_FLAG true)
find_package(Threads REQUIRED)

# SOURCES
include_directories("${PROJECT_SOURCE_DIR}/include")

# COMPILER
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_POSITION_INDEPENDENT_CODE true)

# OUTPUT
add_library(memalc SHARED "src/memalc.c")
add_library(pthreadsem STATIC "src/pthreadsem.c")
target_link_libraries(memalc Threads::Threads)
target_link_libraries(pthreadsem Threads::Threads)
