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

# Versions are set = major.minor.patch
set(NOVILE_VERSION_MAJOR "0")
set(NOVILE_VERSION_MINOR "1")
set(NOVILE_VERSION_PATCH "0")
set(NOVILE_VERSION ${NOVILE_VERSION_MAJOR}.${NOVILE_VERSION_MINOR}.${NOVILE_VERSION_PATCH})

project(novile)

# library .so/.dylib/.dll files will be build in <build_dir>/lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib")

# some debug output for library (useful for debugging)
if(VERBOSE_OUTPUT)
    message(STATUS "Library is going to contain verbose output")
    # allows to use macros NOVILE_VERBOSE_OUTPUT in the source
    add_definitions("-DNOVILE_VERBOSE_OUTPUT")
endif(VERBOSE_OUTPUT)

# we don't need to call moc each time
# and include current dir
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# library is based on webkit widgets + its deps
find_package(Qt5WebKitWidgets REQUIRED)

add_subdirectory(src)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
    message(STATUS "Example application is going to be built")
endif(BUILD_EXAMPLE)

if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(${CMAKE_SOURCE_DIR}/doc/Doxyfile ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(doc ALL
                          ${DOXYGEN_EXECUTABLE}
                          ${CMAKE_BINARY_DIR}/Doxyfile
                          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
                          COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
        message(STATUS "Doxygen API documentation is going to be created")
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)
