cmake_minimum_required(VERSION 3.10)

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
set(CMD_SOURCES
    converter.cpp
    cmd_app.cpp
    cmd_main.cpp)
set(GTK_SOURCES
    converter.cpp
    gtk_app.cpp
    gtk_main.cpp)

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}")
add_executable(converter ${CMD_SOURCES})
add_executable(converter-gtk ${GTK_SOURCES})
target_link_libraries(converter-gtk ${GTKMM_LIBRARIES})
