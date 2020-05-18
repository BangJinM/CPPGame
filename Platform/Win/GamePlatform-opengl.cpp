#include <stdio.h>
#include <tchar.h>
#include "GamePlatform-opengl.h"
#include "IApplication.h"
#include "MemoryManager.h"
#include "InputManager.h"
namespace GameEngine{

GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540);
OpenGLApplication g_App(config);
MemoryManager*   g_pMemoryManager  = static_cast<MemoryManager*>(new MemoryManager);
InputManager*   g_pInputManager  = static_cast<InputManager*>(new InputManager);
IApplication* g_pApp = &g_App;


OpenGLApplication::OpenGLApplication(GfxConfiguration& config):BaseApplication(config) {}

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

	glfwSetMouseButtonCallback(window, mouseInput);
	glfwSetKeyCallback(window, keyInput);

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
	if (action == GLFW_PRESS)
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
}


void OpenGLApplication::calculateDeltaTime()
{
	auto now = std::chrono::steady_clock::now();
	_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
	_lastUpdate = now;
	//_deltaTime = MAX(1, _deltaTime);
}
void OpenGLApplication::Tick()
{
	// glCheckError();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->m_bQuit = glfwWindowShouldClose(window);
	// ((CubeObject*)gameObject)->RendererMaterial();
	// ((GameObject*)gameObjectMaterail)->RendererMaterial();
	// std::string fps = "FPS = " + std::to_string(1000/_deltaTime);
	// std::string de = std::to_string(_deltaTime) + "\n";
	// printf(de.data());
	// text->DrawSprite(fps, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	 glfwSwapBuffers(window);
	 glfwPollEvents();
	// calculateDeltaTime();
}
}