#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showCurrentDirFiles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFileInfoList(QFileInfoList pInfoList)
{

}

void MainWindow::showCurrentDirFiles()
{
    QDir curDir("F:/projects/my/CPPGame");
    QStringList fileList;
    QFileInfoList infoList = curDir.entryInfoList(fileList, QDir::AllEntries);
    this->showFileInfoList(infoList);
}

