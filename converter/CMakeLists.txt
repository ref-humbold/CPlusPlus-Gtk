cmake_minimum_required(VERSION 3.5)
project(converter VERSION 0.3.190612)

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
set(CMD_SOURCES
    "${PROJECT_SOURCE_DIR}/src/converter.cpp"
    "${PROJECT_SOURCE_DIR}/src/cmd_app.cpp"
    "${PROJECT_SOURCE_DIR}/src/cmd_main.cpp")
set(GTK_SOURCES
    "${PROJECT_SOURCE_DIR}/src/converter.cpp"
    "${PROJECT_SOURCE_DIR}/src/gtk_app.cpp"
    "${PROJECT_SOURCE_DIR}/src/gtk_main.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_executable(converter ${CMD_SOURCES})
add_executable(converter-gtk ${GTK_SOURCES})
target_link_libraries(converter-gtk ${GTKMM_LIBRARIES})
