#ifndef EDITOR_P_H
#define EDITOR_P_H

#include <QtCore>
#include <QVBoxLayout>

#include <QtWebKit>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWebKitWidgets>
#endif

#include "editor.h"

namespace Novile
{

/**
 * @brief The EditorPrivate class
 *
 * EditorPrivate class represents low-level wrapper for Ace editor and background of the Editor
 * @see Editor
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

        connect(this, SIGNAL(linesChanged(int)),
                parent, SIGNAL(linesChanged(int)));

        connect(this, SIGNAL(textChanged()),
                parent, SIGNAL(textChanged()));
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

        QObject::connect(aceView, SIGNAL(loadFinished(bool)),
                &loop, SLOT(quit()));

        aceView->load(QUrl("qrc:/html/ace.html"));
        loop.exec();

        // Wrapper (data/wrapper.js)
        QWebFrame *frame = aceView->page()->mainFrame();
        frame->addToJavaScriptWindowObject("Novile", this);

        QFile listeners(":/html/wrapper.js");
        if (listeners.open(QIODevice::ReadOnly))
            executeJavaScript(listeners.readAll());
    }

    /**
     * @brief Escape symbols for JavaScript calls
     * @param text non-escaped code
     * @return escaped code (ready for js call)
     */
    QString escape(const QString &text)
    {
        QString escaped = text;
        escaped.replace("\n", "\\n");
        escaped.replace("\t", "\\t");
        escaped.replace("\'", "\\'");
        escaped.replace("\"", "\\\"");

        return escaped;
    }

public slots:
    /**
     * @brief Provider for linesChanged()
     * @param lines new number of rows
     * @see linesChanged()
     */
    void onLinesChanged(int lines)
    {
        emit linesChanged(lines);
    }

    /**
     * @brief Provider for textChanged()
     * @see textChanged()
     */
    void onTextChanged()
    {
        emit textChanged();
    }

signals:
    /**
     * @brief Intermediate signal for Editor::linesChanged()
     * @see Editor::linesChanged()
     */
    void linesChanged(int);

    /**
     * @brief Intermediate signal for Editor::textChanged()
     * @see Editor::textChanged()
     */
    void textChanged();

public:
    Editor *parent;
    QWebView *aceView;
    QVBoxLayout *layout;
};

} // namespace Novile

#endif // EDITOR_P_H
