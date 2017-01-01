cmake_minimum_required(VERSION 2.8)
project(AnalogClockGtk)

find_package(PkgConfig REQUIRED)

#CHECK FOR gtkmm 3
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
include_directories(${GTKMM3_INCLUDE_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
add_definitions(${GTKMM3_CFLAGS_OTHER})

set(SRC src/main.cpp
        src/window.h
        src/window.cpp)
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
