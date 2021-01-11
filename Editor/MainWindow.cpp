#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QSettings>

#include "FileView.h"
#include "EditorView.h"
#include "OutputView.h"
#include "RuningView.h"
#include "StructureView.h"
#include "PropertiesView.h"

#include "MemoryManager.h"
#include "../File/AssetLoader.h"
#include "AssetManager.h"
#include "BaseGraphicsManager.h"

namespace GameEngine
{
    MemoryManager *g_pMemoryManager = static_cast<MemoryManager *>(new MemoryManager);
    AssetLoader *g_pAssetLoader = static_cast<AssetLoader *>(new AssetLoader);
    AssetManager *g_pAssetManager = static_cast<AssetManager *>(new AssetManager);
    BaseGraphicsManager *g_pGraphicsManager = static_cast<BaseGraphicsManager*>(new BaseGraphicsManager);
} // namespace GameEngine

using namespace GameEngine;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    int ret;

    if ((ret = g_pMemoryManager->Initialize()) != 0)
    {
        printf("App Initialize failed, will exit now.");
    }

    if ((ret = g_pAssetLoader->Initialize()) != 0)
    {
        printf("App Initialize failed, will exit now.");
    }

    if ((ret = g_pAssetManager->Initialize()) != 0)
    {
        printf("App Initialize failed, will exit now.");
    }

    ui->setupUi(this);
    QWidget* p = takeCentralWidget();
    if(p)
        delete p;
    //允许嵌套dock
    setDockNestingEnabled(true);
    setupDockWidgets();
    createActions();

    readSettings();
}

MainWindow::~MainWindow()
{
    g_pAssetLoader->Finalize();
    g_pAssetManager->Finalize();
    g_pMemoryManager->Finalize();
    g_pGraphicsManager->Finalize();

    delete g_pAssetLoader;
    delete g_pAssetManager;
    delete g_pMemoryManager;
    delete g_pGraphicsManager;
    delete ui;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                       tr("GameEngine Editor"));
}

void MainWindow::open()
{
    if (maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::maybeSave()
{
//    if (!ui->plainTextEdit->document()->isModified())
//        return true;
    const QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Application"),
                                                                 tr("The document has been modified.\n"
                                                                    "Do you want to save your changes?"),
                                                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret)
    {
    case QMessageBox::Save:
        return true;
        //        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
    {
//        writeSettings();
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
//    ui->plainTextEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

void MainWindow::documentWasModified()
{
//    setWindowModified(ui->plainTextEdit->document()->isModified());
}

void MainWindow::setupDockWidgets(){
//    auto actionWindow = ui->menu_window;

    FileView* fileView = new FileView();
    addDockWidget(Qt::LeftDockWidgetArea, fileView);
    fileView->show();

    StructureView* structureView = new StructureView();
    addDockWidget(Qt::LeftDockWidgetArea, structureView);
    structureView->show();

    EditorView* editorView = new EditorView();
    addDockWidget(Qt::LeftDockWidgetArea, editorView);
    editorView->show();

    RuningView* runingView = new RuningView();
    addDockWidget(Qt::LeftDockWidgetArea, runingView);
    runingView->show();

    PropertiesView* propertiesView = new PropertiesView();
    addDockWidget(Qt::RightDockWidgetArea, propertiesView);
    propertiesView->show();

    OutputView* outputView = new OutputView();
    addDockWidget(Qt::BottomDockWidgetArea, outputView);
    outputView->show();

    splitDockWidget(structureView, outputView, Qt::Vertical);
    splitDockWidget(structureView, editorView, Qt::Horizontal);
    splitDockWidget(editorView, runingView, Qt::Horizontal);
    splitDockWidget(runingView, propertiesView, Qt::Horizontal);

    tabifyDockWidget(outputView, fileView);

    resizeDocks({fileView, editorView, runingView, propertiesView},{100, 300, 300,100},Qt::Horizontal);
    resizeDocks({outputView, editorView},{100,500},Qt::Vertical);

    ui->menu_window->addAction(fileView->toggleViewAction());
    ui->menu_window->addAction(outputView->toggleViewAction());
    ui->menu_window->addAction(editorView->toggleViewAction());
    ui->menu_window->addAction(runingView->toggleViewAction());
    ui->menu_window->addAction(propertiesView->toggleViewAction());
    ui->menu_window->addAction(structureView->toggleViewAction());
//    actionWindow->addMenu(fileView->colorSwatchMenu());
}

void MainWindow::createActions()
{
    connect(ui->about, &QAction::triggered, this, &MainWindow::about);
    connect(ui->about_qt, &QAction::triggered, this, &QApplication::aboutQt);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::open);
    connect(ui->action_close, &QAction::triggered, this, &QWidget::close);
//    connect(ui->plainTextEdit->document(), &QTextDocument::contentsChanged, this, &MainWindow::documentWasModified);
}

void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.", "Icon Editor");

    settings.beginGroup("mainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "Icon Editor");

    settings.beginGroup("mainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    settings.endGroup();
}
