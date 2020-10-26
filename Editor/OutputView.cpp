#include "OutputView.h"
#include "ui_OutputView.h"

OutputView::OutputView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::OutputView)
{
    ui->setupUi(this);
}

OutputView::~OutputView()
{
    delete ui;
}
