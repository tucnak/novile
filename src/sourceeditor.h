#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include "novile_export.h"
#include <QObject>

namespace Novile
{

class NOVILE_EXPORT SourceEditor : public QObject
{
    Q_OBJECT
public:
    explicit SourceEditor(QObject *parent = 0);
    
signals:
    
public slots:
    
};

} // namespace Novile

#endif // SOURCEEDITOR_H
