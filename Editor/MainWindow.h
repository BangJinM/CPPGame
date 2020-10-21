#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QIcon>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void menuClick();

    ///在QListWidget里显示当前目录下的明细
    void showFileInfoList(QFileInfoList pInfoList);

    ///根据文件性质获取图标
    ///iType=1:文件夹
    ///iType=2:文件
    QIcon *getItemPropertyIcon(int iType);

    ///显示当前目录下的文件夹和文件
    void showCurrentDirFiles();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
