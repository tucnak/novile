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
    sourceeditor.cpp
)

set(NOVILE_HEADERS
    sourceeditor.h
    novile_export.h
    novile_debug.h
)

set(NOVILE_MOC_HEADERS
    sourceeditor.h
)

set(NOVILE_RESOURCES
    ../shared/shared.qrc
)

add_library(novile SHARED ${NOVILE_SOURCES} ${NOVILE_HEADERS} ${NOVILE_MOC_HEADERS})
target_link_libraries(novile ${Qt5WebKit_LIBRARIES})
qt5_use_modules(novile WebKit)
qt5_add_resources(novile ${NOVILE_RESOURCES})

set_target_properties(novile PROPERTIES
    DEFINE_SYMBOL NOVILE_MAKEDLL
    PUBLIC_HEADER "${NOVILE_HEADERS}"
)

#INSTALL(TARGETS novile
#    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
#)
