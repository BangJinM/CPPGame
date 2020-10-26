#ifndef STRUCTUREVIEW_H
#define STRUCTUREVIEW_H

#include <QDockWidget>

namespace Ui {
class StructureView;
}

class StructureView : public QDockWidget
{
    Q_OBJECT

public:
    explicit StructureView(QWidget *parent = nullptr);
    ~StructureView();

private:
    Ui::StructureView *ui;
};

#endif // STRUCTUREVIEW_H
