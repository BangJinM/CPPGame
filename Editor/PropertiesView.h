#ifndef PROPERTIESVIEW_H
#define PROPERTIESVIEW_H

#include <QDockWidget>

namespace Ui {
class PropertiesView;
}

class PropertiesView : public QDockWidget
{
    Q_OBJECT

public:
    explicit PropertiesView(QWidget *parent = nullptr);
    ~PropertiesView();

private:
    Ui::PropertiesView *ui;
};

#endif // PROPERTIESVIEW_H
