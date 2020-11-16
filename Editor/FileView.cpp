#include "FileView.h"
#include "ui_FileView.h"

#include <QFileSystemModel>
#include <QDir>


FileView::FileView(QWidget *parent) : QDockWidget(parent),
                                      ui(new Ui::FileView)
{
    ui->setupUi(this);

    _fileRootPath = "E:/games/fgcq/fgcq_tools";
    _curPath = _fileRootPath;

    init();
}

FileView::~FileView()
{
    delete _listModel;
    delete _treeModel;
    delete ui;
}

void FileView::init(){
    _treeModel = new QFileSystemModel();
    _treeModel->setRootPath(QDir::currentPath()); //_logDir

    ui->treeView->setModel(_treeModel);
    ui->treeView->setRootIndex(_treeModel->index(_fileRootPath));

    //隐藏文件名后面的信息
    for (int i = 1; i < _treeModel->columnCount(); i++)
    {
        ui->treeView->setColumnHidden(i, true);
    }

    _listModel = new QFileSystemModel();
    _listModel->setRootPath(QDir::currentPath());
    ui->listView->setModel(_listModel);
    ui->listView->setViewMode(QListView::IconMode); //ListMode
    ui->listView->setRootIndex(_listModel->index(_curPath));
}

void FileView::setRootPath(QString path){
    _fileRootPath = path;
    setTreeDir(_fileRootPath);
    setListDir(_fileRootPath);
}

void FileView::setTreeDir(QString treePath){
    _treeModel->setRootPath(treePath);
    ui->treeView->setRootIndex(_treeModel->index(treePath));
}

void FileView::setListDir(QString listPath){
    _listModel->setRootPath(listPath);
    ui->listView->setRootIndex(_listModel->index(listPath));
}

void FileView::on_treeView_doubleClicked(const QModelIndex &index)
{
    QFileInfo var = _listModel->fileInfo(index);
    if(var.isDir())
        setListDir(var.filePath());
}

void FileView::on_listView_doubleClicked(const QModelIndex &index)
{
    QFileInfo var = _listModel->fileInfo(index);
    if(var.isDir())
        setListDir(var.filePath());
    if (var.isFile())
        printf("dsadasdasdas");
}
