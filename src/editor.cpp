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
#include <QtWebKitWidgets>
#include "novile_debug.h"
#include "editor.h"
#include "editor_p.h"

namespace Novile
{

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    d(new EditorPrivate(this))
{
    d->startAceWidget();
    d->executeJavaScript("editor.focus()");
}

Editor::~Editor()
{
}

void Editor::copy()
{
    QString text;
    text = d->executeJavaScript("editor.getCopyText()").toString();
    if (!text.isEmpty()) {
        QClipboard *clip = qApp->clipboard();
        clip->setText(text, QClipboard::Clipboard);
    }
}

void Editor::paste()
{
    QClipboard *clip = qApp->clipboard();
    QString text = clip->text(QClipboard::Clipboard);
    if (!text.isEmpty())
        d->executeJavaScript(QString("editor.insert('%1')").arg(text)).toString();
}

void Editor::cut()
{
    copy();
    d->executeJavaScript("editor.remove(editor.getSelectionRange())");
}

int Editor::lines() const
{
    return d->executeJavaScript("property('lines')").toInt();
}

void Editor::gotoLine(int lineNumber) const
{
    d->executeJavaScript("editor.gotoLine("+QString::number(lineNumber)+")");
}

QString Editor::text() const
{
    return d->executeJavaScript("property('text')").toString();
}

void Editor::setText(const QString &newText)
{
    d->executeJavaScript("editor.setValue('"+newText+"')");
    d->executeJavaScript("editor.selection.clearSelection()");
}

bool Editor::isReadOnly() const
{
    return d->executeJavaScript("editor.getReadOnly()").toBool();
}

void Editor::setReadOnly(bool readOnly)
{
    if (readOnly) {
        d->executeJavaScript("editor.setReadOnly(true)");
    } else {
        d->executeJavaScript("editor.setReadOnly(false)");
    }
}

void Editor::showPrintMargin()
{
    d->executeJavaScript("editor.setShowPrintMargin(true)");
}

void Editor::hidePrintMargin()
{
    d->executeJavaScript("editor.setShowPrintMargin(false)");
}

int Editor::fontSize()
{
    return  d->executeJavaScript("document.getElementById('editor').style.fontSize")
            .toString()
            .replace("px", "")
            .toInt();
}

void Editor::setFontSize(int px)
{
    d->executeJavaScript("document.getElementById('editor').style.fontSize='" +
                         QString::number(px) + "px';");
}

void Editor::setHighlightMode(HighlightMode mode)
{
    switch(mode) {
    case ModeCpp:
        setHighlightMode(QString("c_cpp"), QUrl("qrc:/ace/mode-c_cpp.js"));
        return;
    case ModeCss:
        setHighlightMode(QString("css"), QUrl("qrc:/ace/mode-css.js"));
        return;
    case ModeHtml:
        setHighlightMode(QString("html"), QUrl("qrc:/ace/mode-html.js"));
        return;
    case ModeJavaScript:
        setHighlightMode(QString("javascript"), QUrl("qrc:/ace/mode-javascript.js"));
        return;
    case ModePascal:
        setHighlightMode(QString("pascal"), QUrl("qrc:/ace/mode-pascal.js"));
        return;
    case ModePhp:
        setHighlightMode(QString("php"), QUrl("qrc:/ace/mode-php.js"));
        return;
    case ModePython:
        setHighlightMode(QString("python"), QUrl("qrc:/ace/mode-python.js"));
        return;
    case ModeRuby:
        setHighlightMode(QString("ruby"), QUrl("qrc:/ace/mode-ruby.js"));
        return;
    case ModeXml:
        setHighlightMode(QString("xml"), QUrl("qrc:/ace/mode-xml.js"));
        return;
    }
}

void Editor::setHighlightMode(const QString &name, const QUrl &url)
{
    const QString request = ""
            "$.getScript('"+url.toString()+"');"
            "editor.getSession().setMode('ace/mode/"+name+"');";

    d->executeJavaScript(request);
}

void Editor::setTheme(Theme theme)
{
    switch(theme) {
    case ThemeAmbiance:
        setTheme(QString("ambiance"), QUrl("qrc:/ace/theme-ambiance.js"));
        return;
    case ThemeMonokai:
        setTheme(QString("monokai"), QUrl("qrc:/ace/theme-monokai.js"));
        return;
    case ThemeTextMate:
        setTheme(QString("textmate"), QUrl("qrc:/ace/theme-textmate.js"));
        return;
    }
}

void Editor::setTheme(const QString &name, const QUrl &url)
{
    const QString request = ""
            "$.getScript('"+url.toString()+"');"
            "editor.setTheme('ace/theme/"+name+"');";

    d->executeJavaScript(request);
}

bool Editor::eventFilter(QObject *object, QEvent *filteredEvent)
{
    Q_UNUSED(object);

    // Key press filters
    if (filteredEvent->type() == QEvent::KeyPress) {
        QKeyEvent *event = (QKeyEvent*)filteredEvent;

        int mod = event->modifiers();
        int key = event->key();

        if (mod == Qt::ControlModifier && key == Qt::Key_C) {
            copy();
            return true;
        }

        if (mod == Qt::ControlModifier && key == Qt::Key_V) {
            paste();
            return true;
        }

        if (mod == Qt::ControlModifier && key == Qt::Key_X) {
            cut();
            return true;
        }
    }
    return false;
}

} // namespace Novile
