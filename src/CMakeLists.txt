#
# This file is part of the Novile Editor
#
# This program is free software licensed under the GNU LGPL. You can
# find a copy of this license in LICENSE in the top directory of
# the source code.
#
# Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
#

set(NOVILE_SOURCES
    editor.cpp
)

set(NOVILE_HEADERS
    editor.h
    novile_export.h
    novile_debug.h
    editor_p.h
)

qt5_add_resources(NOVILE_RCC_SRC ../data/shared.qrc)
add_library(novile SHARED ${NOVILE_SOURCES}
                          ${NOVILE_HEADERS}
                          ${NOVILE_RCC_SRC}
                          ../data/shared.qrc
)
qt5_use_modules(novile WebKitWidgets)

set_target_properties(novile PROPERTIES
    DEFINE_SYMBOL NOVILE_MAKEDLL
    PUBLIC_HEADER "${NOVILE_HEADERS}"
)

install(TARGETS novile
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)
