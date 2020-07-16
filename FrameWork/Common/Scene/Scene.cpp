#include "Scene.h"
#include "Mesh.h"

//һ�²���
#include "ObjParser.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "AssetLoader.h"
#include "TextureParser.h"
#include "Transform.h"
#include "MyMath.h"
#include "OpenGLDebugger.h"
#include "SceneParser.h"

namespace GameEngine
{
	extern AssetLoader *g_pAssetLoader;

	Scene::Scene()
	{
		gameObject = new GameObject();
		gameObject->setName("root");
		SceneParser::Parse("Scene/default.scene", this);
		updateCamera(gameObject);
	}

	void Scene::updateCamera(BaseObject* gb)
	{
		auto children = gb->getChildren();

		for (auto i = children.begin(); i != children.end(); i++)
		{
			auto camera = i->second->getComponent<Camera>();
			if(camera)
				m_Cameras.push_back(camera);
			updateCamera(i->second);
		}
	}

	Scene::~Scene()
	{
		delete gameObject;
		m_Cameras.clear();
	}

	void Scene::Draw()
	{
		GlmMat4 viewMx, projectMx;
		if (m_Cameras.size()>0)
		{
			viewMx = m_Cameras[0]->m_Host->getComponent<Transform>()->getMatrix();
			projectMx = m_Cameras[0]->getProjectionMatrix();
			auto children = gameObject->getChildren();
			for ( auto i = children.begin(); i != children.end() ; i++)
			{
				GameObject* gb = (GameObject *)i->second;
				gb->Draw(viewMx, projectMx);
			}
			
		}
	}
} // namespace GameEngine