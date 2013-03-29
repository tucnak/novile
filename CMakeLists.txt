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

if(VERBOSE_OUTPUT)
	message(STATUS "Executable will contain verbose output")
	add_definitions("-DNOVILE_VERBOSE_OUTPUT")
endif(VERBOSE_OUTPUT)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5WebKit REQUIRED)

set(NOVILE_BUILD_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(LIBRARY_OUTPUT_PATH  "${NOVILE_BUILD_DIRECTORY}")
set(LIBRARY_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIBRARY_INSTALL_PATH}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

add_subdirectory(src)
