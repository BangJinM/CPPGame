#include "Scene.h"
#include "Mesh.h"

//һ�²���
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "MyMath.h"
#include "OpenGLDebugger.h"
#include "SceneParser.h"
#include "glfw/glfw3.h"

namespace GameEngine
{
	Scene::Scene()
	{
		gameObject = GameObject::createGameObject();
		gameObject->setName("root");
		SceneParser::Parse("Scene/defaultEx.scene", this);
	}

	void Scene::updateCamera(std::shared_ptr<GameObject> gb)
	{
		// auto children = gb->getChildren();

		// for (auto i = children.begin(); i != children.end(); i++)
		// {
		// 	auto camera = i->second->getComponent<Camera>();
		// 	if (camera)
		// 		m_Cameras.push_back(camera);
		// 	auto light = i->second->getComponent<Light>();
		// 	if (light)
		// 		m_Lights.push_back(light);
		// 	updateCamera(i->second);
		// }
	}

	Scene::~Scene()
	{
		// m_Cameras.clear();
		// m_Lights.clear();
	}

	void Scene::Update()
	{
		// m_Cameras.clear();
		// m_Lights.clear();
		// updateCamera(gameObject);
		// GlmMat4 viewMx, projectMx;
		// if (m_Cameras.size() > 0)
		// {
		//m_Cameras[0]->m_Parent->getComponent<Transform>()->setRotation(vecterFloat3( 0, glfwGetTime() * 5, 0));
		// viewMx = m_Cameras[0]->getParent()->getComponent<Transform>()->getMatrix();
		// projectMx = m_Cameras[0]->getProjectionMatrix();
		auto children = gameObject->getChildren();
		for (auto i = children.begin(); i != children.end(); i++)
		{
			i->second->Update();
		}
		// }
	}
} // namespace GameEngine