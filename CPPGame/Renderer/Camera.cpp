#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 rotation, glm::float32 near, glm::float32 far,glm::float32 width , glm::float32 height)
	:m_Position(position),m_Rotation(rotation),m_Near(near),m_Far(far),m_ScreenWidth(width), m_ScreenHeight(height){
	this->updateCameraMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
	return this->m_ViewMatrix4;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->m_ProjectionMatrix4;
}

void Camera::updateCameraMatrix()
{
	//
	glm::mat4 model = glm::mat4(1);
	//ƽ��
	model = glm::translate(model, m_Position);
	//��ת
	glm::qua<float> qua = glm::qua<float>(glm::radians(m_Rotation));
	model = model * glm::mat4_cast(qua);
	//�۲����
	m_ViewMatrix4 = model;
	//ͶӰ����
	m_ProjectionMatrix4 = glm::perspective(glm::radians(m_FieldofView), m_ScreenWidth / m_ScreenHeight, this->m_Near, this->m_Far);
}
