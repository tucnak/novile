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
     * @brief Short way of cursorPosition()
     * @return line, on which cursor is located
     * @see cursorPosition
     */
    int currentLine();

    /**
     * @brief Short way of cursorPosition()
     * @return column, on which cursor is located
     * @see cursorPosition
     */
    int currentColumn();

    /**
     * @brief Current position of the cursor in the document
     * @param row coordinates: line
     * @param column coordinates: position from the left
     */
    void cursorPosition(int *row, int *column);

    /**
     * @brief Set position of the cursor in the document
     * @param row coordinates: line
     * @param column coordinates: position from the left
     */
    void setCursorPosition(int row, int column);

    /**
     * @brief Number of source lines
     * @return lines in the source
     */
    int lines() const;

    /**
     * @brief Number of symbols in the @p row
     * @param row
     * @return number of screenrows in a wrapped line
     */
    int lineLength(int row) const;

    /**
     * @brief Information stored int the @p row
     * @param row line, chosen for iteration
     * @return string with line contents
     */
    QString line(int row) const;

    /**
     * @brief Changes cursor position (=row) to set
     * @param lineNumber new cursor's row
     */
    void gotoLine(int lineNumber) const;

    /**
     * @brief Insert @p text at the current cursor position
     * @param text information to be inserted
     */
    void insert(const QString &text);

    /**
     * @brief Insert @p text at the @p row and @p column
     * @param row coordinates: line
     * @param column coordinates: position from the left
     * @param text information to be inserted
     */
    void insert(int row, int column, const QString &text);

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
     * @brief Get selected text from the editor
     * @return selected texts
     */
    QString selectedText() const;

    /**
     * @brief Remove selected text from the editor
     */
    void removeSelectedText();

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
     * @param mode lexer entry from the HighlightMode
     * @see HighlightMode
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
     * @param theme entry from the Theme
     * @see Theme
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
