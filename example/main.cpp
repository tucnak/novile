/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

#include <QtCore>
#include <QApplication>
#include "mainwindow.h"

using namespace Novile;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.showMaximized();

    return app.exec();
}
