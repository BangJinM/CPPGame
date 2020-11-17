#include "OpenGLWidget.h"

#include <QOpenGLContext>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void OpenGLWidget::paintGL(){
}

void OpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

void OpenGLWidget::resizeGL(int width, int height){
    glViewport(0,0,width,height);
}
