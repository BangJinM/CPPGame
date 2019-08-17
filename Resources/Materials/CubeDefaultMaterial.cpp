#include "CubeDefaultMaterial.h"

#include "Renderer/GameObject.h"
#include "Renderer/Transform.h"
#include "Renderer/Camera.h"

CubeDefaultMaterial::CubeDefaultMaterial(Object* camera):Material(camera){
	m_Camera = camera;
	m_Shader = ResourceManager::LoadShader("Resources/Shaders/DefaultCube.vs", "Resources/Shaders/DefaultCube.flag", nullptr, "cube");
	m_Texture = *ResourceManager::GetTexture("Resources/Textures/container.jpg");
}

CubeDefaultMaterial::~CubeDefaultMaterial() {}

void CubeDefaultMaterial::Use(Object* host)
{
	if (nullptr == host || nullptr == m_Camera)
		return;
	auto* cameraClass = m_Camera->getComponent<Camera>(ClassID(Camera));
	auto* cameraTrans = m_Camera->getComponent<Transform>(ClassID(Transform));
	if (nullptr == cameraClass || nullptr == cameraTrans)
		return;

	auto model = host->getComponent<Transform>(ClassID(Transform))->getTransformMatrix4();
	auto view = cameraTrans->getTransformMatrix4();
	auto projection = cameraClass->getProjectionMatrix();

	m_Shader.Use();
	m_Shader.SetMatrix4("projection", projection);
	m_Shader.SetMatrix4("model", model);
	m_Shader.SetMatrix4("view", view);

	glActiveTexture(GL_TEXTURE0);
	m_Texture.Bind();
}

