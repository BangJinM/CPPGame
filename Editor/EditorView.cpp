#include "EditorView.h"
#include "ui_EditorView.h"

#include "OpenGLWidget.h"

EditorView::EditorView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::EditorView)
{
    ui->setupUi(this);
    openGlWidget = new OpenGLWidget(ui->verticalWidget);
    openGlWidget->show();
}

EditorView::~EditorView()
{
    delete ui;
}
