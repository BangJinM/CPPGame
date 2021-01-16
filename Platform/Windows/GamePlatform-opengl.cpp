﻿#include <stdio.h>
#include <tchar.h>
#include "GamePlatform-opengl.h"
#include "IApplication.h"

namespace GameEngine
{
	OpenGLApplication::OpenGLApplication(GfxConfiguration &config) : BaseApplication(config) {}

	int OpenGLApplication::Initialize()
	{
		int result = 0;
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw window creation
		// --------------------
		window = glfwCreateWindow(m_Config.screenWidth, m_Config.screenHeight, "CPPGame", NULL, NULL);
		if (window == NULL)
		{
			printf("Failed to create GLFW window");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize GLAD");
			return -1;
		}
		glViewport(0, 0, m_Config.screenWidth, m_Config.screenHeight);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

		return result;
	}

	void OpenGLApplication::Finalize()
	{
	}

	void OpenGLApplication::calculateDeltaTime()
	{
		auto now = std::chrono::steady_clock::now();
		_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
		_lastUpdate = now;
	}
	void OpenGLApplication::Tick()
	{
		this->m_bQuit = glfwWindowShouldClose(window);
	}
} // namespace GameEngine