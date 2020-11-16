#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QDockWidget>
#include <QFileSystemModel>

namespace Ui {
class FileView;
}

class FileView : public QDockWidget
{
    Q_OBJECT

public:
    void setRootPath(QString path);
    explicit FileView(QWidget *parent = nullptr);
    ~FileView();

private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_listView_doubleClicked(const QModelIndex &index);
private:

    void init();
    void setTreeDir(QString);
    void setListDir(QString);
private:
    Ui::FileView *ui;

    QFileSystemModel *_listModel;
    QFileSystemModel *_treeModel;
    QString _fileRootPath = "";
    QString _curPath = "";
};

#endif // FILEVIEW_H
