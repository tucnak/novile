#include <QtCore>
#include <QVBoxLayout>
#include <QWebView>
#include "novile_debug.h"
#include "sourceeditor.h"

namespace Novile
{

class SourceEditorPrivate
{
public:
    SourceEditorPrivate(SourceEditor *p = 0) :
        parent(p),
        aceView(new QWebView(p)),
        layout(new QVBoxLayout(p))
    {
        parent->setLayout(layout);
        layout->addWidget(aceView);
    }

    ~SourceEditorPrivate()
    {
    }

    void loadAceView()
    {
        aceView->setUrl(QUrl(":/ace.html"));
    }

private:
    SourceEditor *parent;
    QWebView *aceView;
    QVBoxLayout *layout;
};

SourceEditor::SourceEditor(QWidget *parent) :
    QWidget(parent),
    d(new SourceEditorPrivate(this))
{
    d->loadAceView();
}

SourceEditor::~SourceEditor()
{
}

} // namespace Novile
