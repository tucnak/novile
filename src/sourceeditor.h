/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include <QWidget>
#include "novile_export.h"

namespace Novile
{

class SourceEditorPrivate;
class NOVILE_EXPORT SourceEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SourceEditor(QWidget *parent = 0);
    ~SourceEditor();

private:
    SourceEditorPrivate * const d;
    
};

} // namespace Novile

#endif // SOURCEEDITOR_H
