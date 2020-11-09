#include "Widget.h"
#include "MyMath.h"
#include "Shader.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "AssetManager.h"
#include "CanvasRenderer.h"
GameEngineBegin

Widget::Widget() : Component(ClassID(Widget))
{
}

Widget::~Widget()
{
}

void Widget::InitComponent(SharedGameObject host)
{
	Component::InitComponent(host);
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
	auto scene = SceneManager::GetInstance()->GetScene();
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


GameEngineEnd