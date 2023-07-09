cmake_minimum_required(VERSION 3.10)

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
set(LIB_SOURCES "converter.cpp")
set(CMD_SOURCES
    "cmd_app.cpp"
    "cmd_main.cpp")
set(GTK_SOURCES
    "gtk_app.cpp"
    "gtk_main.cpp")

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXE_OUTPUT_DIR})
add_executable(${CMD_EXE_NAME} ${CMD_SOURCES})
target_link_libraries(${CMD_EXE_NAME} ${LIB_NAME})

add_executable(${GTK_EXE_NAME} ${GTK_SOURCES})
target_link_libraries(${GTK_EXE_NAME}
                      ${LIB_NAME}
                      ${GTKMM_LIBRARIES})
