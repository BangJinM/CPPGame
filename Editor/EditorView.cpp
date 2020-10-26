#include "EditorView.h"
#include "ui_EditorView.h"

EditorView::EditorView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::EditorView)
{
    ui->setupUi(this);
}

EditorView::~EditorView()
{
    delete ui;
}
