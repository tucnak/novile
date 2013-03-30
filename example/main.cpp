/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

#include <QApplication>
#include "editor.h"
#include "novile_debug.h"

using namespace Novile;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Editor editor;
    editor.setWindowTitle("Novile Demonstration");
    editor.setGeometry(100, 50, 1000, 600);
    editor.show();
    editor.setHighlightMode(Editor::ModeCpp);
    editor.setTheme(Editor::ThemeTextMate);

    return app.exec();
}
