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

set(EXAMPLE_SOURCES main.cpp)

set(FILES_IMPORT ../src/sourceeditor.cpp)

add_executable(example ${EXAMPLE_SOURCES} ${FILES_IMPORT})
qt5_use_modules(example WebKitWidgets)
