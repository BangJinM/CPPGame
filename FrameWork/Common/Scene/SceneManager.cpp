#include "SceneManager.h"
#include "Scene.h"

GameEngineBegin

SharePtr<SceneManager>	
SceneManager::m_SceneManager;

SharePtr<SceneManager> SceneManager::GetInstance()
{
	if (m_SceneManager)
		return m_SceneManager;
	m_SceneManager = SharePtr<SceneManager>(new SceneManager());
	return m_SceneManager;
}

void SceneManager::SetNextScene(SharePtr<Scene> scene)
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

SharePtr<Scene> SceneManager::GetScene()
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
GameEngineEnd