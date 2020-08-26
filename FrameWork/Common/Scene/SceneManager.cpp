#include "SceneManager.h"
#include "Scene.h"
namespace GameEngine
{
	std::shared_ptr<SceneManager> SceneManager::m_SceneManager;

	std::shared_ptr<SceneManager> SceneManager::GetInstance()
	{
		if (m_SceneManager)
			return m_SceneManager;
		m_SceneManager = std::shared_ptr<SceneManager>(new SceneManager());
		return m_SceneManager;
	}

	void SceneManager::SetNextScene(std::shared_ptr<Scene> scene)
	{
		nextScene = scene;
	}

	void SceneManager::ChangeScene()
	{
		if (!nextScene)
			return;
		curScene = nextScene;
		nextScene = nullptr;
	}

	std::shared_ptr<Scene> SceneManager::GetScene()
	{
		if (curScene)
			return curScene;
		return std::make_shared<Scene>();
	}

	SceneManager::~SceneManager()
	{
	}

	SceneManager::SceneManager()
	{
		curScene = std::make_shared<Scene>();
		nextScene = nullptr;
	}

	void SceneManager::Update()
	{
		if (!curScene)
			curScene = std::make_shared<Scene>();
		curScene->Update();
		curScene->RenderAll();
	}
} // namespace GameEngine