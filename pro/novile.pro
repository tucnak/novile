QT = core gui webkit
TARGET = novile
TEMPLATE = lib
DESTDIR = ../lib

VERSION = 0.5.0

DEFINES += \
	NOVILE_MAKEDLL \
	NOVILE_QT4

SOURCES = \
	../src/editor.cpp

HEADERS = \
    ../src/editor.h \
    ../src/novile_export.h \
    ../src/novile_debug.h \
    ../src/editor_p.h
	
RESOURCES = \
	../data/shared.qrc

OTHER_FILES += \
    ../deploy/make_deb.py \
    ../data/html/wrapper.js \
    ../data/html/ace.html
