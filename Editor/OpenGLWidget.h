#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_3_3_Core>

#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

#include "BaseGraphicsManager.h"
using namespace GameEngine;


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

    int _width;
    int _height;

    virtual int Initialize();
    virtual void Finalize();

    virtual void Tick();
    virtual void Clear();
    virtual void Draw(std::list<RendererCammand> m_RendererCommands);

    void BindTexture(SharedTexture texture);
    void PrepareMesh(SharedMesh mesh, int index);
    void PrepareMaterial(GameEngine::Material &material);

protected:
    virtual void initializeGL() Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    virtual void paintGL() Q_DECL_OVERRIDE;

    QOpenGLContext *m_context;
signals:

};

#endif // OPENGLWIDGET_H
