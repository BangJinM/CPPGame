#include "StructureView.h"
#include "ui_StructureView.h"

StructureView::StructureView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::StructureView)
{
    ui->setupUi(this);
}

StructureView::~StructureView()
{
    delete ui;
}
