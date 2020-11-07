#include "InputManagerWindows.h"
#include <utility>

GameEngineBegin
int InputManagerWindows::Initialize()
{
	window = glfwGetCurrentContext();
	glfwSetMouseButtonCallback(window, mouseInput);
	glfwSetKeyCallback(window, keyInput);
	return InputManager::Initialize();
}

void InputManagerWindows::mouseInput(GLFWwindow *window, int key, int action, int mods)
{
}

void InputManagerWindows::keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
}

void InputManagerWindows::Tick()
{
	InputManager::Tick();
	glfwPollEvents();
}

GameEngineEnd