#include "PropertiesView.h"
#include "ui_PropertiesView.h"

PropertiesView::PropertiesView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PropertiesView)
{
    ui->setupUi(this);
}

PropertiesView::~PropertiesView()
{
    delete ui;
}
