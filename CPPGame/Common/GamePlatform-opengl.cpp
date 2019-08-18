#include <stdio.h>
#include <tchar.h>
#include "GamePlatform-opengl.h"
#include "Renderer/ResourceManager.h"
#include "glm/glm.hpp"

#include "Renderer/ClassIDs.h"
#include "Renderer/GameObject.h"
#include "Renderer/Transform.h"

#include "Renderer/TextRenderer.h"
#include "Renderer/Camera.h"
#include "Renderer/SpriteRenderer.h"
#include "..//Resources/Materials/SpriteDefaultMaterial.h"
#include "..//Resources/Materials/CubeDefaultMaterial.h"
#include "Renderer/CubeRenderer.h"
#include "OpenGLDebug.h"

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

TextRenderer* text;
Object* gameObject;
Object* gameObjectMaterail;
GameObject* cameraObject;

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
	glEnable(GL_DEPTH_TEST);

	glfwSetMouseButtonCallback(window, mouseInput);
	glfwSetKeyCallback(window, keyInput);


	ResourceManager::LoadShader("Resources/Shaders/DefaultText.vs", "Resources/Shaders/DefaultText.flag", nullptr, "text");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(m_Config.screenWidth), 0.0f, static_cast<GLfloat>(m_Config.screenHeight));
	ResourceManager::GetShader("text")->Use();
	ResourceManager::GetShader("text")->SetMatrix4("projection", projection);
	text = new TextRenderer(ResourceManager::GetShader("text"));

	ResourceManager::LoadShader("Resources/Shaders//Default.vs", "Resources/Shaders/Default.flag", nullptr, "sprite");
	glm::mat4 projection1 = glm::ortho(0.0f, static_cast<GLfloat>(this->m_Config.screenWidth), static_cast<GLfloat>(this->m_Config.screenHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection1);

	//gameObject = new GameObject();
	//Transform* trans = new Transform();
	//trans->SetLocalPosition(glm::vec3(m_Config.screenWidth/2, m_Config.screenHeight/2, 0));
	//trans->SetLocalRotation(glm::vec3(0, 0, 45));
	//trans->SetLocalScale(glm::vec3(0.5, 0.5, 0.5));
	//SpriteRenderer* renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	//gameObject->addComponent(trans->getClassID(), trans);
	//gameObject->addComponent(renderer->getClassID(), renderer);



	gameObjectMaterail = new GameObject();
	Transform* materialTrans = new Transform();
	materialTrans->SetLocalPosition(glm::vec3(200, 200, 0));
	materialTrans->SetLocalScale(glm::vec3(0.5, 0.5, 0.5));

	cameraObject = new GameObject();
	Camera* camera = new Camera(CameraType::Orthographic, m_Config.screenWidth, m_Config.screenHeight);
	cameraObject->addComponent(camera->getClassID(), camera);

	Material* material = new SpriteDefaultMaterial(cameraObject);

	SpriteRenderer* srm = new SpriteRenderer(ResourceManager::GetShader("sprite"), material);

	gameObjectMaterail->addComponent(srm->getClassID(),srm);
	gameObjectMaterail->addComponent(materialTrans->getClassID(),materialTrans);

	ResourceManager::LoadShader("Resources/Shaders/DefaultCube.vs", "Resources/Shaders/DefaultCube.flag", nullptr, "cube");

	cameraObject =new GameObject();
	Transform* cameraTranform = new Transform();
	Camera *cameraCube = new Camera();
	cameraTranform->SetLocalPosition(glm::vec3(0,0,1));
	cameraObject->addComponent(cameraTranform->getClassID(), cameraTranform);
	cameraObject->addComponent(cameraCube->getClassID(), cameraCube);

	cameraObject->getComponent<Transform>(ClassID(Transform))->getTransformMatrix4();
	cameraObject->getComponent<Camera>(ClassID(Camera))->getProjectionMatrix();

	CubeDefaultMaterial* cdm = new CubeDefaultMaterial(cameraObject);

	gameObject = new CubeObject();
	Transform* transCube = new Transform();
	transCube->SetLocalPosition(glm::vec3(0, 0, -3));
	transCube->SetLocalRotation(glm::vec3(0, 45, 45));
	transCube->SetLocalScale(glm::vec3(1, 1, 1));

	CubeRenderer* rendererCube = new CubeRenderer(ResourceManager::GetShader("cube"), cdm);
	gameObject->addComponent(transCube->getClassID(), transCube);
	gameObject->addComponent(rendererCube->getClassID(), rendererCube);
	_lastUpdate = std::chrono::steady_clock::now();


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


void OpenGLApplication::calculateDeltaTime()
{
	auto now = std::chrono::steady_clock::now();
	_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
	_lastUpdate = now;
	//_deltaTime = MAX(1, _deltaTime);
}

void OpenGLApplication::Tick()
{
	glCheckError();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->m_bQuit = glfwWindowShouldClose(window);

	((CubeObject*)gameObject)->RendererMaterial();
	((GameObject*)gameObjectMaterail)->RendererMaterial();
	std::string fps = "FPS = " + std::to_string(1000/_deltaTime);
	std::string de = std::to_string(_deltaTime) + "\n";
	printf(de.data());
	text->DrawSprite(fps, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	glfwSwapBuffers(window);
	glfwPollEvents();
	calculateDeltaTime();
}
