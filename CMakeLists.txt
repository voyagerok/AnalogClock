cmake_minimum_required(VERSION 2.8)
project(AnalogClockGtk)

#check for boost
find_package(Boost 1.62 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#check for pkgconfig
find_package(PkgConfig REQUIRED)

#CHECK FOR gtkmm 3
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
include_directories(${GTKMM3_INCLUDE_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
add_definitions(${GTKMM3_CFLAGS_OTHER})

set(SRC src/main.cpp
        src/window.h
        src/window.cpp
        src/clock_widget.h
        src/clock_widget.cpp
        src/logger.h
        src/logger.cpp)
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES}
                                      ${Boost_LIBRARIES})
