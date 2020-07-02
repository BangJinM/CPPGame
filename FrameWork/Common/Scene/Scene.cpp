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
		transform->setPosition(vecterFloat3(0.0f, 0.0f, -20.f));

		GameObject *cameraObject = new GameObject();
		cameraObject->addComponent(camera);
		cameraObject->addComponent(transform);
		m_Gameobjects.push_back(cameraObject);

		auto gameobject = ObjParser::Parse("Scene/Shape_Cube.obj", "Materials/");
		Shader* shader = new Shader(g_pAssetLoader->SyncOpenAndReadTextFileToString("Shaders/default.vert"), g_pAssetLoader->SyncOpenAndReadTextFileToString("Shaders/default.frag"));
		OpenGLDebugger::glCheckError();
		for (size_t i = 0; i < gameobject->m_Materials.size(); i++)
		{
			gameobject->m_Materials[i]->setShader(shader);
		}

		Transform *transformG = new Transform();
		transformG->setScale(glm::vec3(1.f / 50, 1.f / 50, 1.f / 50));
		m_Gameobjects.push_back(gameobject);
		gameobject->addComponent(transformG);
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
		GlmMat4 viewMx, projectMx;
		if (m_Cameras[0])
		{
			viewMx = m_Cameras[0]->m_Host->getComponent<Transform>()->getMatrix();
			projectMx = m_Cameras[0]->getProjectionMatrix();
		}
		for (size_t i = 0; i < m_Gameobjects.size(); i++)
		{
			m_Gameobjects[i]->Draw(viewMx, projectMx);
		}
	}
} // namespace GameEngine