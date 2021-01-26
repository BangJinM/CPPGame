﻿#include "Scene.h"

//һ�²���
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

#include "MyMath.h"
#include "UI/CanvasRenderer.h"

GameEngineBegin

Scene::Scene()
{
	m_Root = GameObject::createGameObject();
	m_Root->setName("root");

	auto canvas = GameObject::createGameObject();
	canvas->setName("Canvas");
	m_Root->addChild(canvas);
	canvas->addComponent<CanvasRenderer>(std::make_shared<CanvasRenderer>());
}

void Scene::AddGameObject(SharedGameObject gameobject)
{
	GetRootGameObject()->addChild(gameobject);
}

void Scene::AddGameObject(SharedGameObject gameobject, SharedGameObject parent)
{
}

SharedGameObject Scene::GetRootGameObject() { return m_Root; }

Scene::~Scene()
{
	m_Cameras.clear();
	m_Renderers.clear();
}

void Scene::Start()
{
	auto children = m_Root->getChildren();
	for (auto i = children.begin(); i != children.end(); i++)
	{
		i->second->Start();
	}
}

void Scene::Update()
{
	auto children = m_Root->getChildren();
	for (auto i = children.begin(); i != children.end(); i++)
	{
		i->second->Update();
	}
}

void Scene::Destory()
{
	auto children = m_Root->getChildren();
	for (auto i = children.begin(); i != children.end(); i++)
	{
		i->second->Destory();
	}
}

void Scene::RemoveCamera(SharePtr<Camera> camera)
{
	for (auto i = m_Cameras.begin(); i != m_Cameras.end(); i++)
	{
		if (*i == camera)
			m_Cameras.erase(i);
	}
}

void Scene::AddCamera(SharePtr<Camera> camera)
{
	m_Cameras.push_back(camera);
}

void Scene::AddLight(SharePtr<Light> light)
{
	m_Lights.push_back(light);
}

void Scene::RemoveLight(SharePtr<Light> light)
{
	for (auto i = m_Lights.begin(); i != m_Lights.end(); i++)
	{
		if (*i == light)
			m_Lights.erase(i);
	}
}

void Scene::AddRenderer(SharePtr<Renderer> reenderer)
{
	m_Renderers.push_back(reenderer);
}

void Scene::RemoveRenderer()
{
}

SharePtr<CanvasRenderer> Scene::GetCanvasRenderer()
{
	return m_Canvas;
}

void Scene::SetCanvasRenderer(SharePtr<CanvasRenderer> canvas)
{
	m_Canvas = canvas;
}

SharedGameObject Scene::GetGObject(SharedGameObject parent, int sid)
{
	std::map<std::string, SharedGameObject> children;
	if (parent)
		children = parent->getChildren();
	else
		children = GetRootGameObject()->getChildren();
	SharedGameObject result;
	for (auto i = children.begin(); i != children.end(); i++)
	{
		auto child = i->second;
		if (child->GetId() == sid)
			result = child;
		if (result)
			return result;
		auto result = GetGObject(child, sid);
		if (result)
			return result;
	}
	return SharedGameObject();
}
GameEngineEnd
