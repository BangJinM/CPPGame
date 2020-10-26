#ifndef RUNINGVIEW_H
#define RUNINGVIEW_H

#include <QDockWidget>

namespace Ui {
class RuningView;
}

class RuningView : public QDockWidget
{
    Q_OBJECT

public:
    explicit RuningView(QWidget *parent = nullptr);
    ~RuningView();

private:
    Ui::RuningView *ui;
};

#endif // RUNINGVIEW_H
