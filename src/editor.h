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
class NOVILE_EXPORT Editor : public QWidget
{
    Q_OBJECT
public:
    enum HighlightMode {
        ModeCpp = 0,
        ModeCss,
        ModeHtml,
        ModeJavaScript,
        ModePascal,
        ModePhp,
        ModePython,
        ModeRuby,
        ModeXml
    };

    enum Theme {
        ThemeAmbiance = 0,
        ThemeMonokai,
        ThemeTextMate
    };

    explicit Editor(QWidget *parent = 0);
    ~Editor();

    void setHighlightMode(HighlightMode mode);
    void setHighlightMode(const QString &name, const QUrl &url);

    void setTheme(Theme theme);
    void setTheme(const QString &name, const QUrl &url);

private:
    EditorPrivate * const d;
    
};

} // namespace Novile

#endif // EDITOR_H
