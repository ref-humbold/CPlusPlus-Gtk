cmake_minimum_required(VERSION 3.5)
project(traceroute VERSION 1.2)

# COMPILER
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# SOURCES
include_directories("${PROJECT_SOURCE_DIR}/include")
set(SOURCES
    "${PROJECT_SOURCE_DIR}/src/RawSocket.cpp"
    "${PROJECT_SOURCE_DIR}/src/IPAddress.cpp"
    "${PROJECT_SOURCE_DIR}/src/ICMPReceiver.cpp"
    "${PROJECT_SOURCE_DIR}/src/ICMPSender.cpp"
    "${PROJECT_SOURCE_DIR}/src/ICMPController.cpp"
    "${PROJECT_SOURCE_DIR}/src/traceroute.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_executable(traceroute ${SOURCES})
