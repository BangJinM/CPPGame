#include "EidtorView.h"
#include "ui_EidtorView.h"

EidtorView::EidtorView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::EidtorView)
{
    ui->setupUi(this);
}

EidtorView::~EidtorView()
{
    delete ui;
}
