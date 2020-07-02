#include "Camera.h"
#include "GameObject.h"
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

} // namespace GameEngine