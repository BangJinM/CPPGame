#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QIcon>
#include <QDir>
#include <QPlainTextEdit>

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

    void about();

    void open();

    bool maybeSave();
    void documentWasModified();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupDockWidgets();
    void createActions();
    void loadFile(const QString& fileName);
    void setCurrentFile(const QString &fileName);

    QString curFile;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
