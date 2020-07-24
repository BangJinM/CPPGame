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
		gameObject = new GameObject();
		gameObject->setName("root");
		SceneParser::Parse("Scene/default.scene", this);
	}

	void Scene::updateCamera(BaseObject *gb)
	{
		auto children = gb->getChildren();

		for (auto i = children.begin(); i != children.end(); i++)
		{
			auto camera = i->second->getComponent<Camera>();
			if (camera)
				m_Cameras.push_back(camera);
			updateCamera(i->second);
		}
	}

	Scene::~Scene()
	{
		m_Cameras.clear();
		delete gameObject;
	}

	void Scene::Draw()
	{
		m_Cameras.clear();
		updateCamera(gameObject);
		GlmMat4 viewMx, projectMx;
		if (m_Cameras.size() > 0)
		{
			//m_Cameras[0]->m_Host->getComponent<Transform>()->setRotation(vecterFloat3( 0, glfwGetTime() * 5, 0));
			viewMx = m_Cameras[0]->m_Host->getComponent<Transform>()->getMatrix();
			projectMx = m_Cameras[0]->getProjectionMatrix();
			auto children = gameObject->getChildren();
			for (auto i = children.begin(); i != children.end(); i++)
			{
				GameObject *gb = (GameObject *)i->second;
				gb->Draw(viewMx, projectMx);
			}
		}
	}
} // namespace GameEngine