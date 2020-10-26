#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <QDockWidget>

namespace Ui {
class OutputView;
}

class OutputView : public QDockWidget
{
    Q_OBJECT

public:
    explicit OutputView(QWidget *parent = nullptr);
    ~OutputView();

private:
    Ui::OutputView *ui;
};

#endif // OUTPUTVIEW_H
