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

namespace GameEngine
{
	extern AssetLoader *g_pAssetLoader;

	Scene::Scene()
	{
		initScene();
		updateCamera();
	}

	void Scene::initScene()
	{
		Camera *camera = new Camera();
		Transform *transform = new Transform();
		GameObject *cameraObject = new GameObject();
		cameraObject->addComponent(camera);
		cameraObject->addComponent(transform);
		m_Gameobjects.push_back(cameraObject);


		auto gameobject = ObjParser::Parse("Scene/model.obj", "Materials/");
		Transform *transformG = new Transform();
		m_Gameobjects.push_back(gameobject);
		gameobject->addComponent(transformG);

		
		Shader shader(g_pAssetLoader->SyncOpenAndReadTextFileToString("Shader/default.vert"), g_pAssetLoader->SyncOpenAndReadTextFileToString("Shader/default.flag"));

		for (size_t i = 0; i < gameobject->m_Materials.size(); i++)
		{
			gameobject->m_Materials[i]->setShader(&shader);
		}
		
	}


	void Scene::updateCamera()
	{
		for (size_t i = 0; i < m_Gameobjects.size(); i++)
		{
			auto camera = m_Gameobjects[i]->getComponent<Camera>();
			m_Cameras.push_back(camera);
		}
		
	}

	void Scene::addChild(BaseObject *child)
	{
	}

	void Scene::deleteChild(BaseObject *child)
	{
	}

	Scene::~Scene()
	{
		m_Gameobjects.clear();
		m_Cameras.clear();
	}

	void Scene::Draw()
	{
		if (m_Cameras[0])
		for (size_t i = 0; i < m_Gameobjects.size(); i++)
		{
			m_Gameobjects[i]->Draw();
		}
	}
} // namespace GameEngine