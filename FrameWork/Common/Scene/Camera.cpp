#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
namespace GameEngine
{
	Camera::Camera(glm::float32 near, glm::float32 far, glm::float32 width, glm::float32 height)
		: m_Near(near), m_Far(far), m_ScreenWidth(width), m_ScreenHeight(height), Component(ClassID(Camera))
	{
	}

	glm::mat4 Camera::getViewMatrix()
	{
		return this->m_ViewMatrix4;
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		//观察矩阵
		auto m_ViewMatrix4 = m_Host->getComponent<Transform>()->getMatrix();

		//投影矩阵
		m_ProjectionMatrix4 = glm::perspective(glm::radians(m_FieldofView), m_ScreenWidth / m_ScreenHeight, this->m_Near, this->m_Far);
		return this->m_ProjectionMatrix4;
	}

} // namespace GameEngine