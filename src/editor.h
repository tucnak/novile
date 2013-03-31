/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include "novile_export.h"

namespace Novile
{

class EditorPrivate;

/**
 * @brief The Editor class
 *
 * Editor class implements top-level wrapper, based on Qt for Ace editor
 */
class NOVILE_EXPORT Editor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int lines READ lines NOTIFY linesChanged)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
public:
    /**
     * @brief Default highlight lexers
     */
    enum HighlightMode {
        /// C++ programming language
        ModeCpp = 0,
        /// CSS markup language
        ModeCss,
        /// HTML markup language
        ModeHtml,
        /// JavaScript scripting language
        ModeJavaScript,
        /// Pascal programming language
        ModePascal,
        /// PHP scripting language
        ModePhp,
        /// Python programming language
        ModePython,
        /// Ruby programming language
        ModeRuby,
        /// XML markup language
        ModeXml
    };

    /**
     * @brief Default editor themes
     */
    enum Theme {
        /// Ambiance-style theme
        ThemeAmbiance = 0,
        /// Monokai-style theme
        ThemeMonokai,
        /// Textmate-style theme
        ThemeTextMate
    };

    /**
     * @brief Regular constructor
     * @param parent widget, used as parent
     */
    explicit Editor(QWidget *parent = 0);
    ~Editor();

    /**
     * @brief Copy selected text to the buffer
     */
    void copy();

    /**
     * @brief Paste text from the buffer to the editor
     */
    void paste();

    /**
     * @brief Cut selected text to the buffer
     */
    void cut();

    /**
     * @brief Number of source lines
     * @return lines in the source
     */
    int lines() const;

    /**
     * @brief Changes cursor position (=row) to set
     * @param lineNumber new cursor's row
     */
    void gotoLine(int lineNumber) const;

    /**
     * @brief Source code from editor
     * @return source code
     */
    QString text() const;

    /**
     * @brief Set source code for editor
     * @param newText new source code
     */
    void setText(const QString &newText);

    /**
     * @brief Can we edit or not?
     * @return can or not
     */
    bool isReadOnly() const;

    /**
     * @brief Allow edit or not
     * @param readOnly yes or not
     */
    void setReadOnly(bool readOnly);

    /**
     * @brief Show print margin (semi-transparent line at right)
     */
    void showPrintMargin();

    /**
     * @brief Hide print margin (semi-transparent line at right)
     */
    void hidePrintMargin();

    /**
     * @brief Font size of the source text
     * @return size in pixels
     */
    int fontSize();

    /**
     * @brief Set font size in pixels
     * @param px size in pixels
     */
    void setFontSize(int px);

    /**
     * @brief Set default syntax highlighter lexer
     * @param mode lexer entry from @see HighlightMode
     */
    void setHighlightMode(HighlightMode mode);

    /**
     * @brief Set specific syntax highlighter lexer
     * @param name string, set into "ace/mode/$name"
     * @param url lexer javascript source url
     */
    void setHighlightMode(const QString &name, const QUrl &url);

    /**
     * @brief Set default editor theme
     * @param theme entry from @see Theme
     */
    void setTheme(Theme theme);

    /**
     * @brief Set specific editor theme
     * @param name string, set into "ace/theme/$name"
     * @param url theme javascript source url
     */
    void setTheme(const QString &name, const QUrl &url);

protected:
    bool eventFilter(QObject *object, QEvent *filteredEvent);

signals:
    /**
     * @brief New number of lines in the document
     */
    void linesChanged(int);

    /**
     * @brief New text of the document
     */
    void textChanged();

private:
    EditorPrivate * const d;
};

} // namespace Novile

#endif // EDITOR_H
