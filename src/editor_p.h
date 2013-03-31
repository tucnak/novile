#ifndef EDITOR_P_H
#define EDITOR_P_H

#include <QtCore>
#include <QtWebKitWidgets>
#include "editor.h"

namespace Novile
{

/**
 * @brief The EditorPrivate class
 *
 * EditorPrivate class represents low-level wrapper for Ace editor and background of @see Editor
 */

class EditorPrivate: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Regular constructor
     * @param p editor object (will be used like Q-pointer)
     */
    EditorPrivate(Editor *p = 0) :
        QObject(),
        parent(p),
        aceView(new QWebView(p)),
        layout(new QVBoxLayout(p))
    {
        parent->setLayout(layout);
        layout->addWidget(aceView);
        layout->setMargin(0);

        aceView->installEventFilter(parent);

        connect(this, &EditorPrivate::linesChanged,
                parent, &Editor::linesChanged);

        connect(this, &EditorPrivate::textChanged,
                parent, &Editor::textChanged);
    }

    ~EditorPrivate()
    {
    }

    /**
     * @brief Run some JS code to Ace
     * @param code javascript source
     * @return evaluation result
     */
    QVariant executeJavaScript(const QString &code)
    {
        return aceView->page()->mainFrame()->evaluateJavaScript(code);
    }

    /**
     * @brief Start Ace web widget and load javascript low-level helpers
     */
    void startAceWidget()
    {
        QEventLoop loop(parent);
        QObject::connect(aceView, &QWebView::loadFinished,
                         &loop, &QEventLoop::quit);
        aceView->load(QUrl("qrc:/html/ace.html"));
        loop.exec();

        // Wrapper (data/wrapper.js)
        QWebFrame *frame = aceView->page()->mainFrame();
        frame->addToJavaScriptWindowObject("Novile", this);

        QFile listeners(":/html/wrapper.js");
        if (listeners.open(QIODevice::ReadOnly))
            executeJavaScript(listeners.readAll());
    }

public slots:
    /**
     * @brief Provider for @see linesChanged()
     * @param lines new number of rows
     */
    void onLinesChanged(int lines)
    {
        emit linesChanged(lines);
    }

    /**
     * @brief Provider for @see textChanged()
     */
    void onTextChanged()
    {
        emit textChanged();
    }

signals:
    /**
     * @brief Intermediate signal for @see Editor::linesChanged()
     */
    void linesChanged(int);

    /**
     * @brief Intermediate signal for @see Editor::textChanged()
     */
    void textChanged();

public:
    Editor *parent;
    QWebView *aceView;
    QVBoxLayout *layout;
};

} // namespace Novile

#endif // EDITOR_P_H
