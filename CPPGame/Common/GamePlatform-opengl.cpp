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
GameObject* gameObject;

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


	ResourceManager::LoadShader("Resources/Shaders/DefaultText.vs", "Resources/Shaders/DefaultText.flag", nullptr, "text");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(m_Config.screenWidth), 0.0f, static_cast<GLfloat>(m_Config.screenHeight));
	ResourceManager::GetShader("text")->Use();
	ResourceManager::GetShader("text")->SetMatrix4("projection", projection);
	text = new TextRenderer(*ResourceManager::GetShader("text"));

	ResourceManager::LoadShader("Resources/Shaders//Default.vs", "Resources/Shaders/Default.flag", nullptr, "sprite");
	glm::mat4 projection1 = glm::ortho(0.0f, static_cast<GLfloat>(this->m_Config.screenWidth), static_cast<GLfloat>(this->m_Config.screenHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection1);

	gameObject = new GameObject();
	Transform* trans = new Transform();
	trans->SetLocalPosition(glm::vec3(m_Config.screenWidth/2, m_Config.screenHeight/2, 0));
	trans->SetLocalRotation(glm::vec3(0, 0, 45));
	trans->SetLocalScale(glm::vec3(0.5, 0.5, 0.5));
	SpriteRenderer* renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	gameObject->addComponent(trans->getClassID(), trans);
	gameObject->addComponent(renderer->getClassID(), renderer);
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
	gameObject->Renderer();
	text->DrawSprite("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	glfwSwapBuffers(window);
	glfwPollEvents();
}
