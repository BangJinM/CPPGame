#ifndef EIDTORVIEW_H
#define EIDTORVIEW_H

#include <QDockWidget>

namespace Ui {
class EidtorView;
}

class EidtorView : public QDockWidget
{
    Q_OBJECT

public:
    explicit EidtorView(QWidget *parent = nullptr);
    ~EidtorView();

private:
    Ui::EidtorView *ui;
};

#endif // EIDTORVIEW_H
