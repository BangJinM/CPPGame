#include "EditorView.h"
#include "ui_EditorView.h"

#include "CoreFunctionWidget.h"
#include "BaseGraphicsManager.h"

EditorView::EditorView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::EditorView)
{
    ui->setupUi(this);
    openGlWidget = new CoreFunctionWidget();
    openGlWidget->show();
    ui->verticalLayout->addWidget(openGlWidget);
}

EditorView::~EditorView()
{
    delete ui;
}
