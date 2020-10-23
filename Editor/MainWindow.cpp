#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about(){
    QMessageBox::about(this, tr("About"),
             tr("GameEngine Editor"));
}

void MainWindow::open()
//! [5] //! [6]
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::loadFile(const QString &fileName)
//! [46] //! [47]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    ui->plainTextEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::setCurrentFile(const QString &fileName)
//! [46] //! [47]
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

void MainWindow::createActions(){
    connect(ui->about, &QAction::triggered, this, &MainWindow::about);
    connect(ui->about_qt, &QAction::triggered, this, &QApplication::aboutQt);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::open);
    connect(ui->action_close, &QAction::triggered, this, &QWidget::close);
}
