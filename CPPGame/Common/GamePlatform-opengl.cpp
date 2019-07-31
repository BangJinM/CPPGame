#include <stdio.h>
#include <tchar.h>
#include "GamePlatform-opengl.h"
#include "ResourceManager.h"
#include "Renderer/SpriteRenderer.h"
#include "glm/glm.hpp"
SpriteRenderer * Renderer;
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

	glfwSetMouseButtonCallback(window, mouseInput);
	glfwSetKeyCallback(window, keyInput);


	ResourceManager::LoadShader("CPPGame/Renderer/shaders/Default.vs", "CPPGame/Renderer/shaders/Default.frag", nullptr, "sprite");
	// Configure shaders
//	(T left, T right, T bottom, T top, T zNear, T zFar)
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->m_Config.screenWidth), static_cast<GLfloat>(this->m_Config.screenHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("G:/CPPGame/Game/Textures/awesomeface.png", GL_TRUE, "face");
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));


	return result;
}

//typedef void (* GLFWkeyfun)(GLFWwindow*,int,int,int,int);
//typedef void (* GLFWmousebuttonfun)(GLFWwindow*,int,int,int);
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
	glfwSwapBuffers(window);
	glfwPollEvents();
	Renderer->DrawSprite(*ResourceManager::GetTexture("face"),
		glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
