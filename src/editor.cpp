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
#include <QClipboard>
#include <QShortcut>

#include <QtWebKit>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWebKitWidgets>
#endif

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

    new QShortcut(QKeySequence("Ctrl+A"), this, SLOT(selectAll()));
}

Editor::~Editor()
{
}

void Editor::copy()
{
    QString text = selectedText();
    if (!text.isEmpty()) {
        QClipboard *clip = QApplication::clipboard();
        clip->setText(text, QClipboard::Clipboard);
    }
}

void Editor::paste()
{
    QClipboard *clip = QApplication::clipboard();
    QString text = clip->text(QClipboard::Clipboard);
    if (!text.isEmpty())
        d->executeJavaScript(QString("editor.insert('%1')").arg(d->escape(text))).toString();
}

void Editor::cut()
{
    copy();
    removeSelectedText();
}

void Editor::selectAll()
{
    d->executeJavaScript("editor.selectAll()");
}

void Editor::cursorPosition(int *row, int *column)
{
    *row = currentLine();
    *column = currentColumn();
}

void Editor::setCursorPosition(int row, int column)
{
    if (lines() > row && lineLength(row) >= column) {
        d->executeJavaScript(
                    QString("editor.moveCursorTo(%1, %2)").arg(row).arg(column)
        );
    }
}

int Editor::currentLine()
{
    return d->executeJavaScript("editor.getCursorPosition().row").toInt();
}

int Editor::currentColumn()
{
    return d->executeJavaScript("editor.getCursorPosition().column").toInt();
}

int Editor::lines() const
{
    return d->executeJavaScript("property('lines')").toInt();
}

QString Editor::line(int row) const
{
    return d->executeJavaScript(
                QString("editor.getSession().getLine(%1)").arg(row)
           ).toString();
}

int Editor::lineLength(int row) const
{
    return line(row).length();
}

void Editor::gotoLine(int lineNumber) const
{
    d->executeJavaScript("editor.gotoLine("+QString::number(lineNumber)+")");
}

void Editor::insert(const QString &text)
{
    d->executeJavaScript(QString("editor.insert('%1')").arg(d->escape(text)));
}

void Editor::insert(int row, int column, const QString &text)
{
    if (lines() > row && lineLength(row) > column) {
        int previousLine, previousColumn;
        cursorPosition(&previousLine, &previousColumn);

        setCursorPosition(row, column);
        insert(text);

        // Imaging, that we had this string:
        // hello, novile edit|or! ("|" - cursor pos)
        // then, if we insert smth before cursor pos
        // e.g. after "hello, ", we insert "cool "
        // we have another string:
        // hello, cool novile| editor! ("|" - cursor pos)
        // so, we need to move it 5 sumbols right,
        // which equals text.size()
        if (row == previousLine) {
            if (previousColumn >= column)
                previousColumn += text.size();
        }

        setCursorPosition(previousLine, previousColumn);
    }
}

bool Editor::isIndentationShown()
{
    return d->executeJavaScript("editor.getDisplayIndentGuides()").toBool();
}

void Editor::setIndentationShown(bool is)
{
    QString request = "editor.setDisplayIndentGuides(%1)";
    d->executeJavaScript(request.arg(is));
}

bool Editor::isInvisiblesShown()
{
    return d->executeJavaScript("editor.renderer.getShowInvisibles()").toBool();
}

void Editor::setInvisiblesShown(bool is)
{
    QString request = "editor.renderer.setShowInvisibles(%1)";
    d->executeJavaScript(request.arg(is));
}

bool Editor::isGutterShown()
{
    return d->executeJavaScript("editor.renderer.getShowGutter()").toBool();
}

void Editor::setGutterShown(bool is)
{
    QString request = "editor.renderer.setShowGutter(%1)";
    d->executeJavaScript(request.arg(is));
}

bool Editor::isFadeFoldMarker()
{
    return d->executeJavaScript("editor.getFadeFoldWidgets()").toBool();
}

void Editor::setFadeFoldMarker(bool is)
{
    QString request = "editor.setFadeFoldWidgets(%1)";
    d->executeJavaScript(request.arg(is));
}

bool Editor::isHighlightSelectedWord()
{
    return d->executeJavaScript("editor.getHighlightSelectedWord()").toBool();
}

void Editor::setHighlightSelectedWord(bool is)
{
    QString request = "editor.setHighlightSelectedWord(%1)";
    d->executeJavaScript(request.arg(is));
}

bool Editor::isActiveLineHighlighted()
{
    return d->executeJavaScript("editor.getHighlightActiveLine()").toBool();
}

void Editor::setActiveLineHighlighted(bool is)
{
    QString request = "editor.setHighlightActiveLine(%1)";
    d->executeJavaScript(request.arg(is));
}

QString Editor::text() const
{
    return d->executeJavaScript("editor.getSession().getValue()").toString();
}

void Editor::setText(const QString &newText)
{
    const QString request = "editor.getSession().setValue('%1')";
    d->executeJavaScript(request.arg(d->escape(newText)));
    int lastLine = lines()-1;
    setCursorPosition(lastLine, lineLength(lastLine));
}

QString Editor::selectedText() const
{
    return d->executeJavaScript("editor.getCopyText()").toString();
}

void Editor::removeSelectedText()
{
    d->executeJavaScript("editor.remove(editor.getSelectionRange())");
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
    const QString request = "document.getElementById('editor').style.fontSize='%1px'";
    d->executeJavaScript(request.arg(px));
}

void Editor::setHighlightMode(int mode)
{
    switch(mode) {
    case ModeCpp:
        setHighlightMode("c_cpp");
        return;
    case ModeCss:
        setHighlightMode("css");
        return;
    case ModeHtml:
        setHighlightMode("html");
        return;
    case ModeJavaScript:
        setHighlightMode("javascript");
        return;
    case ModePascal:
        setHighlightMode("pascal");
        return;
    case ModePhp:
        setHighlightMode("php");
        return;
    case ModePython:
        setHighlightMode("python");
        return;
    case ModeRuby:
        setHighlightMode("ruby");
        return;
    case ModeXml:
        setHighlightMode("xml");
        return;
    case ModeActionScript:
        setHighlightMode("actionscript");
        return;
    case ModeAda:
        setHighlightMode("ada");
        return;
    case ModeAssemblyX86:
        setHighlightMode("assembly_x86");
        return;
    case ModeBatch:
        setHighlightMode("batchfile");
        return;
    case ModeClojure:
        setHighlightMode("clojure");
        return;
    case ModeCoffeeScript:
        setHighlightMode("coffee");
        return;
    case ModeCSharp:
        setHighlightMode("csharp");
        return;
    case ModeErlang:
        setHighlightMode("erlang");
        return;
    case ModeGo:
        setHighlightMode("golang");
        return;
    case ModeHaskell:
        setHighlightMode("haskell");
        return;
    case ModeJava:
        setHighlightMode("java");
        return;
    case ModeJson:
        setHighlightMode("json");
        return;
    case ModeLatex:
        setHighlightMode("latex");
        return;
    case ModeLisp:
        setHighlightMode("lisp");
        return;
    case ModeLua:
        setHighlightMode("lua");
        return;
    case ModeMakefile:
        setHighlightMode("makefile");
        return;
    case ModeMarkdown:
        setHighlightMode("markdown");
        return;
    case ModePowershell:
        setHighlightMode("powershell");
        return;
    case ModeScala:
        setHighlightMode("scala");
        return;
    case ModeSh:
        setHighlightMode("sh");
        return;
    case ModeSQL:
        setHighlightMode("sql");
        return;
    }
}

void Editor::setHighlightMode(const QString &name, const QUrl &url)
{
    const QString request = ""
            "$.getScript('%1');"
            "editor.getSession().setMode('ace/mode/%2');";
    d->executeJavaScript(request.arg(url.toString()).arg(name));
}

void Editor::setHighlightMode(const QString &name)
{
    const QString request = ""
            "$.getScript('%1');"
            "editor.getSession().setMode('ace/mode/%2');";
    d->executeJavaScript(request.arg("qrc:/ace/mode-"+name+".js").arg(name));
}

void Editor::setTheme(int theme)
{
    switch(theme) {
    case ThemeAmbiance:
        setTheme("ambiance");
        return;
    case ThemeMonokai:
        setTheme("monokai");
        return;
    case ThemeTextmate:
        setTheme("textmate");
        return;
    case ThemeChaos:
        setTheme("chaos");
        return;
    case ThemeCloudsMidnight:
        setTheme("clouds_midnight");
        return;
    case ThemeEclipse:
        setTheme("eclipse");
        return;
    case ThemeGitHub:
        setTheme("github");
        return;
    case ThemeSolarizedDark:
        setTheme("solarized_dark");
        return;
    case ThemeTomorrowNightBright:
        setTheme("tomorrow_midnight_bright");
        return;
    case ThemeTwilight:
        setTheme("twilight");
        return;
    case ThemeVibrantInk:
        setTheme("vibrant_ink");
        return;
    }
}

void Editor::setTheme(const QString &name, const QUrl &url)
{
    const QString request = ""
            "$.getScript('%1');"
            "editor.setTheme('ace/theme/%2');";
    d->executeJavaScript(request.arg(url.toString()).arg(name));
}

void Editor::setTheme(const QString &name)
{
    const QString request = ""
            "$.getScript('%1');"
            "editor.setTheme('ace/theme/%2');";
    d->executeJavaScript(request.arg("qrc:/ace/theme-"+name+".js").arg(name));
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
