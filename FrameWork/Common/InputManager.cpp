
#include "InputManager.h"
#include <utility>
int GameEngine::InputManager::Initialize()
{
	window = glfwGetCurrentContext();
	glfwSetMouseButtonCallback(window, mouseInput);
	glfwSetKeyCallback(window, keyInput);
	return 0;
}

void GameEngine::InputManager::mouseInput(GLFWwindow *window, int key, int action, int mods)
{
}

void GameEngine::InputManager::keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
}

void GameEngine::InputManager::Finalize()
{
}

void GameEngine::InputManager::Tick()
{
	glfwPollEvents();
}

void GameEngine::InputManager::addClickEventListener(const char key, CallBack callBack)
{
	auto iter = g_pInputManager->_listeners.find(key);

	if (iter == g_pInputManager->_listeners.end())
	{
		GameEngineCallBack *list = new GameEngineCallBack();
		g_pInputManager->_listeners.insert(std::pair<char, GameEngineCallBack *>(key, list));
		addClickEventListener(key, callBack);
		return;
	}
	iter->second->push(callBack);
}

void GameEngine::InputManager::removeClickEventListener(char key, CallBack callBack)
{
	auto iter = g_pInputManager->_listeners.find(key);
	if (iter != g_pInputManager->_listeners.end())
	{
		iter->second->remove(callBack);
	}
}

//
void GameEngine::InputManager::dispatchClickEvent(char key)
{
	auto iter = g_pInputManager->_listeners.find(key);
	int i = 0;
	if (iter != g_pInputManager->_listeners.end())
	{
		iter->second->dispatch();
	}
}
