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
