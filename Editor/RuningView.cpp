#include "RuningView.h"
#include "ui_RuningView.h"

RuningView::RuningView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RuningView)
{
    ui->setupUi(this);
}

RuningView::~RuningView()
{
    delete ui;
}
