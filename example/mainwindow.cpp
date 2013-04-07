#include <QMessageBox>
#include <QtCore>
#include <QComboBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "novile_debug.h"

using namespace Novile;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Novile Editor Demo");

    editor = new Editor(this);

    // Will push left sidebar to the left and minimize it
    ui->mainLayout->insertWidget(1, editor, 1);

    initExampleFiles();
    establishBaseConnects();
    setupStartValues();
}

void MainWindow::establishBaseConnects()
{
    connect(ui->pushAboutNovile, &QPushButton::clicked,
            this, &MainWindow::aboutNovile);

    connect(ui->pushAboutQt, &QPushButton::clicked,
            this, &MainWindow::aboutQt);

    connect(ui->selectDocument,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::updateDocument);

    connect(ui->selectMode,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::updateMode);

    connect(ui->selectTheme,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::updateTheme);

    connect(ui->checkHighlightActive, &QCheckBox::stateChanged,
            this, &MainWindow::updateHighlightActive);

    connect(ui->checkHighlightSelected, &QCheckBox::stateChanged,
            this, &MainWindow::updateHighlightSelected);

    connect(ui->checkShowPrintMargin, &QCheckBox::stateChanged,
            this, &MainWindow::updateShowPrintMargin);

    connect(ui->checkFadeFold, &QCheckBox::stateChanged,
            this, &MainWindow::updateFadeFold);

    connect(ui->checkShowInvisibles, &QCheckBox::stateChanged,
            this, &MainWindow::updateShowInvisibles);

    connect(ui->checkShowGutter, &QCheckBox::stateChanged,
            this, &MainWindow::updateShowGutter);

    connect(ui->checkShowIndent, &QCheckBox::stateChanged,
            this, &MainWindow::updateShowIndent);

    connect(ui->checkReadOnly, &QCheckBox::stateChanged,
            this, &MainWindow::updateReadOnly);
}

void MainWindow::aboutNovile()
{
    QMessageBox::about(this,
                       tr("Novile Source Editor"),
                       tr("Novile is a port of Ace editor into Qt. "
                          "It's distributed in the light-weight shared "
                          "library and can be used in every Qt application "
                          "you want (if it use QtWebkit)"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::updateHighlightActive(int checked)
{
    editor->setActiveLineHighlighted(checked > 0);
}

void MainWindow::updateHighlightSelected(int checked)
{
    editor->setHighlightSelectedWord(checked > 0);
}

void MainWindow::updateShowPrintMargin(int checked)
{
    if (checked > 0) {
        editor->showPrintMargin();
    } else {
        editor->hidePrintMargin();
    }
}

void MainWindow::updateFadeFold(int checked)
{
    editor->setFadeFoldMarker(checked > 0);
}

void MainWindow::updateShowInvisibles(int checked)
{
    editor->setInvisiblesShown(checked > 0);
}

void MainWindow::updateShowGutter(int checked)
{
    editor->setGutterShown(checked > 0);
}

void MainWindow::updateShowIndent(int checked)
{
    editor->setIndentationShown(checked > 0);
}

void MainWindow::updateReadOnly(int checked)
{
    editor->setReadOnly(checked != 0);
}

void MainWindow::updateDocument(int index)
{
    const QString documentText = documents[
            ui->selectDocument->itemText(index)];
    editor->setText(documentText);
    editor->setCursorPosition(0, 0);
}

void MainWindow::updateMode(int index)
{
    editor->setHighlightMode(index);
}

void MainWindow::updateTheme(int index)
{
    editor->setTheme(index);
}

void MainWindow::setupStartValues()
{
    updateDocument(0); // JavaScript document
    ui->selectDocument->setCurrentIndex(0);

    updateMode(3); // JavaScript mode
    ui->selectMode->setCurrentIndex(3);

    updateTheme(2); // Textmate theme
    ui->selectTheme->setCurrentIndex(2);

    updateHighlightActive(true);
    ui->checkHighlightActive->setChecked(true);

    updateHighlightSelected(true);
    ui->checkHighlightSelected->setChecked(true);

    updateFadeFold(false);
    ui->checkFadeFold->setChecked(false);

    updateReadOnly(false);
    ui->checkReadOnly->setChecked(false);

    updateShowGutter(true);
    ui->checkShowGutter->setChecked(true);

    updateShowIndent(true);
    ui->checkShowIndent->setChecked(true);

    updateShowInvisibles(false);
    ui->checkShowInvisibles->setChecked(false);

    updateShowPrintMargin(false);
    ui->checkShowPrintMargin->setChecked(false);
}

void MainWindow::initExampleFiles()
{
    QDir exampleDir(":/documents");
    QStringList exampleFiles = exampleDir.entryList(QDir::Files);
    foreach(const QString &exampleFileName, exampleFiles) {
        const QString filePath = exampleDir.absoluteFilePath(exampleFileName);
        QFile example(filePath);
        if (example.open(QIODevice::ReadOnly)) {
            ui->selectDocument->addItem(exampleFileName);
            documents[exampleFileName] = example.readAll();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editor;
}
