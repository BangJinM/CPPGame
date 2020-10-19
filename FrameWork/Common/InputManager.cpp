#include "InputManager.h"
#include <utility>

GameEngineBegin
int InputManager::Initialize()
{
	window = glfwGetCurrentContext();
	glfwSetMouseButtonCallback(window, mouseInput);
	glfwSetKeyCallback(window, keyInput);
	return 0;
}

void InputManager::mouseInput(GLFWwindow *window, int key, int action, int mods)
{
}

void InputManager::keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
}

void InputManager::Finalize()
{
	
}

void InputManager::Tick()
{
	glfwPollEvents();
}

void InputManager::addClickEventListener(const char key, CallBack callBack)
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

void InputManager::removeClickEventListener(char key, CallBack callBack)
{
	auto iter = g_pInputManager->_listeners.find(key);
	if (iter != g_pInputManager->_listeners.end())
	{
		iter->second->remove(callBack);
	}
}

//
void InputManager::dispatchClickEvent(char key)
{
	auto iter = g_pInputManager->_listeners.find(key);
	int i = 0;
	if (iter != g_pInputManager->_listeners.end())
	{
		iter->second->dispatch();
	}
}
GameEngineEnd