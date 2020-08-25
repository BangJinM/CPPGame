#include "Camera.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
namespace GameEngine
{
	Camera::Camera(glm::float32 near, glm::float32 far, glm::float32 width, glm::float32 height, glm::float32 fieldofView)
		: m_Near(near), m_Far(far), m_ScreenWidth(width), m_ScreenHeight(height), m_FieldofView(fieldofView), Component(ClassID(Camera))
	{
		m_ProjectionMatrix4 = glm::perspective(glm::radians(m_FieldofView), m_ScreenWidth / m_ScreenHeight, this->m_Near, this->m_Far);
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		return this->m_ProjectionMatrix4;
	}

	void Camera::Render(std::list<std::shared_ptr<Renderer>> renderers)
	{
		auto viewMat = getParent()->getComponent<Transform>()->getMatrix();
		auto projectMat = m_ProjectionMatrix4;
		for (auto i = renderers.begin(); i != renderers.end(); i++)
		{
			(*i)->Render(getParent()->getComponent<Camera>());
		}
	}

	void Camera::Update()
	{
		auto camera = getParent()->getComponent<Camera>();
		if (!camera)
			return;
		auto scene = SceneManager::GetInstance()->GetScene();
		scene->AddCamera(std::dynamic_pointer_cast<Camera>(camera));
	}

} // namespace GameEngine