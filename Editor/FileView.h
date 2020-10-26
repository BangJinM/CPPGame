#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QDockWidget>

namespace Ui {
class FileView;
}

class FileView : public QDockWidget
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = nullptr);
    ~FileView();

private:
    Ui::FileView *ui;

    QString curPath = "";
};

#endif // FILEVIEW_H
