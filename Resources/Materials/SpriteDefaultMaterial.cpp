#include "SpriteDefaultMaterial.h"

#include "Renderer/Camera.h"
#include "Renderer/Transform.h"
#include "Renderer/GameObject.h"
#include "Renderer/ResourceManager.h"

SpriteDefaultMaterial::SpriteDefaultMaterial(Object* camera) :Material(camera){
	m_Camera = camera;
	m_Shader = ResourceManager::LoadShader("Resources/Shaders//Default.vs", "Resources/Shaders/Default.flag", nullptr, "sprite");
	m_Texture = *ResourceManager::GetTexture("Resources/Textures/container.jpg");
}

void SpriteDefaultMaterial::Use(Object* host)
{
	if (nullptr == host || nullptr == m_Camera)
		return;
	auto* cameraClass = m_Camera->getComponent<Camera>(ClassID(Camera));
	if (nullptr == cameraClass)
		return;

	auto model = host->getComponent<Transform>(ClassID(Transform))->getTransformMatrix4();
	glm::vec2 imageSize = glm::vec2(m_Texture.Width, m_Texture.Height);
	model = glm::scale(model, glm::vec3(imageSize.x, imageSize.y, 1.0f));

	m_Shader.Use();
	m_Shader.SetMatrix4("projection", cameraClass->getProjectionMatrix());
	m_Shader.SetMatrix4("model", model);
	m_Shader.SetInteger("image", 0);
	m_Shader.SetVector3f("spriteColor", glm::vec3(1.0f));

	glActiveTexture(GL_TEXTURE0);
	m_Texture.Bind();
}

SpriteDefaultMaterial::~SpriteDefaultMaterial() {}