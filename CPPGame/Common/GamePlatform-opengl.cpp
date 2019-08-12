#include <stdio.h>
#include <tchar.h>
#include "GamePlatform-opengl.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/SpriteRenderer.h"
#include "glm/glm.hpp"

#include "Renderer/ClassIDs.h"
#include "Renderer/GameObject.h"
#include "Renderer/Transform.h"

#include "Renderer/TextRenderer.h"

TextRenderer* text;

int OpenGLApplication::Initialize()
{
	int result = 0;
	// glfw: initialize and configure
   // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(m_Config.screenWidth, m_Config.screenHeight, "CPPGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, m_Config.screenWidth, m_Config.screenHeight);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetMouseButtonCallback(window, mouseInput);
	glfwSetKeyCallback(window, keyInput);


	ResourceManager::LoadShader("CPPGame/Renderer/shaders/DefaultText.vs", "CPPGame/Renderer/shaders/DefaultText.flag", nullptr, "text");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(m_Config.screenWidth), 0.0f, static_cast<GLfloat>(m_Config.screenHeight));
	ResourceManager::GetShader("text")->Use();
	ResourceManager::GetShader("text")->SetMatrix4("projection", projection);
	text = new TextRenderer(*ResourceManager::GetShader("text"));
	return result;
}


void OpenGLApplication::Finalize()
{

}

void OpenGLApplication::mouseInput(GLFWwindow* window, int key, int action, int mods)
{
	//if (action == GLFW_PRESS)
	//	if (key == GLFW_MOUSE_BUTTON_LEFT)
	//		glfwSetWindowShouldClose(window, true);
}

void OpenGLApplication::keyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (action == GLFW_PRESS)
	//	if (key == GLFW_KEY_ESCAPE)
	//		glfwSetWindowShouldClose(window, true);
}



void OpenGLApplication::Tick()
{
	this->m_bQuit = glfwWindowShouldClose(window);
	text->DrawSprite("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	glfwSwapBuffers(window);
	glfwPollEvents();
}
