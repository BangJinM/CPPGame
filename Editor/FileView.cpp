#include "FileView.h"
#include "ui_FileView.h"

#include <QFileSystemModel>
#include <QDir>

FileView::FileView(QWidget *parent) : QDockWidget(parent),
                                      ui(new Ui::FileView)
{
    ui->setupUi(this);

    QString _logDir = "E:/games/fgcq/fgcq_tools";
    QFileSystemModel *_fileModel = new QFileSystemModel();
    _fileModel->setRootPath(QDir::currentPath()); //_logDir

    ui->treeView->setModel(_fileModel);
    ui->treeView->setRootIndex(_fileModel->index(_logDir));

    //隐藏文件名后面的信息
    for (int i = 1; i < _fileModel->columnCount(); i++)
    {
        ui->treeView->setColumnHidden(i, true);
    }
}

FileView::~FileView()
{
    delete ui;
}
