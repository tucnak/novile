#include "novile_debug.h"
#include "sourceeditor.h"

namespace Novile
{

SourceEditor::SourceEditor(QObject *parent) :
    QObject(parent)
{
    mDebug() << "Source Editor has been started";
}

} // namespace Novile
