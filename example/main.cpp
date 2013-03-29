#include <QApplication>
#include "../src/sourceeditor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Novile::SourceEditor editor;
    editor.setGeometry(100, 50, 1000, 600);
    editor.show();

    return app.exec();
}
