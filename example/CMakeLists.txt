#
# This file is part of the Novile Editor
#
# This program is free software licensed under the GNU LGPL. You can
# find a copy of this license in LICENSE in the top directory of
# the source code.
#
# Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
#

project(example)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5WebKitWidgets REQUIRED)

set(EXAMPLE_SOURCES main.cpp mainwindow.cpp)
set(EXAMPLE_HEADERS mainwindow.h)

qt5_add_resources(EXAMPLE_RCC_SRC example.qrc)
qt5_wrap_ui(EXAMPLE_UIC_HDR mainwindow.ui)

add_executable(example ${EXAMPLE_SOURCES}
                       ${EXAMPLE_HEADERS}
                       ${EXAMPLE_RCC_SRC}
                       ${EXAMPLE_UIC_HDR}
)

target_link_libraries(example novile)
qt5_use_modules(example WebKitWidgets)
include_directories(${CMAKE_SOURCE_DIR}/src)
