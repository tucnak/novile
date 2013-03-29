#
# This file is part of the Novile Editor
#
# This program is free software licensed under the GNU LGPL. You can
# find a copy of this license in LICENSE in the top directory of
# the source code.
#
# Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
#

cmake_minimum_required(VERSION 2.8.8)

project(novile)

set(NOVILE_BUILD_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${NOVILE_BUILD_DIRECTORY}/lib")

if(VERBOSE_OUTPUT)
    message(STATUS "Library will contain verbose output")
    add_definitions("-DNOVILE_VERBOSE_OUTPUT")
endif(VERBOSE_OUTPUT)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5WebKitWidgets REQUIRED)

add_subdirectory(src)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
    message(STATUS "Example application will be built")
endif(BUILD_EXAMPLE)
