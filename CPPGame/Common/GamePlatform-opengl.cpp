#include <stdio.h>
#include <tchar.h>
#include "GamePlatform-opengl.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/SpriteRenderer.h"
#include "glm/glm.hpp"

#include "Renderer/ClassIDs.h"
#include "Renderer/GameObject.h"
#include "Renderer/Transform.h"

GameObject* gameObject;
GameObject* gameObject1;
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


	ResourceManager::LoadShader("CPPGame/Renderer/shaders/Default.vs", "CPPGame/Renderer/shaders/Default.flag", nullptr, "sprite");
	//// Configure shaders
	////	(T left, T right, T bottom, T top, T zNear, T zFar)
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->m_Config.screenWidth), static_cast<GLfloat>(this->m_Config.screenHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);
	//// Load textures
	ResourceManager::LoadTexture("G:/CPPGame/Game/Textures/awesomeface.png", GL_TRUE);
	//// Set render-specific controls
	SpriteRenderer* renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	gameObject = new GameObject();
	gameObject1 = new GameObject();
	Transform *trans1 = new Transform();
	Transform *trans = new Transform();

	trans->SetLocalPosition(glm::vec3(400, 400, 0));

	trans1->SetLocalPosition(glm::vec3(100, 100, 0));
	trans1->SetLocalScale(glm::vec3(1, 0.5, 1));

	gameObject->addComponent(trans->getClassID(), trans);
	gameObject->addComponent(renderer->getClassID(), renderer);

	gameObject1->addComponent(trans1->getClassID(), trans1);
	gameObject1->addComponent(renderer->getClassID(), renderer);

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
	gameObject1->Renderer();
	glfwSwapBuffers(window);
	glfwPollEvents();
}
