#include "FileView.h"
#include "ui_FileView.h"

FileView::FileView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);
}

FileView::~FileView()
{
    delete ui;
}
