cmake_minimum_required(VERSION 3.10)

# PACKAGES
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# SOURCES
set(SOURCES
    "gtk_app.cpp"
    "lotto.cpp"
    "lotto_game.cpp")

set(OLD_SOURCES "../lotto.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXE_OUTPUT_DIR})
add_executable(${CMD_EXE_NAME} ${OLD_SOURCES})
add_executable(${GTK_EXE_NAME} ${SOURCES})
target_link_libraries(${GTK_EXE_NAME} ${GTKMM_LIBRARIES})
