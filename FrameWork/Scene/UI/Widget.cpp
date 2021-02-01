#include "Widget.h"

#include "AssetManager.h"
#include "CanvasRenderer.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Scene.h"
#include "SceneManager.h"
namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    Widget::Widget() : Component(ClassID(Widget))
    {
    }

    Widget::~Widget()
    {
    }

    void Widget::InitComponent(SharedGameObject host)
    {
        Component::SetParent(host);
    }

    void Widget::setCanvasRenderer(SharePtr<CanvasRenderer> canvasRenderer)
    {
    }

    void Widget::Start()
    {
        if (m_Started)
            return;
        auto widget = getParent()->getComponent<Widget>();
        if (!widget)
            return;
        auto scene = g_pSceneManager->GetScene();
        auto canvas = scene->GetCanvasRenderer();
        if (!canvas)
            return;
        canvas->addWidget(widget);
        Component::Start();
    }

    SharedMaterial Widget::GetMaterial()
    {
        return m_Material;
    }

}  // namespace GameEngine