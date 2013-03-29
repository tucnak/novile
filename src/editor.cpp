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
#include <QVBoxLayout>
#include <QWebView>
#include <QWebFrame>
#include "novile_debug.h"
#include "editor.h"

namespace Novile
{

class EditorPrivate
{
public:
    EditorPrivate(Editor *p = 0) :
        parent(p),
        aceView(new QWebView(p)),
        layout(new QVBoxLayout(p))
    {
        parent->setLayout(layout);
        layout->addWidget(aceView);
        layout->setMargin(0);
    }

    ~EditorPrivate()
    {
    }

    void loadAceView()
    {
        aceView->setUrl(QUrl("qrc:/html/ace.html"));
    }

private:
    Editor *parent;
    QWebView *aceView;
    QVBoxLayout *layout;
};

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    d(new EditorPrivate(this))
{
    d->loadAceView();
}

Editor::~Editor()
{
}

} // namespace Novile
