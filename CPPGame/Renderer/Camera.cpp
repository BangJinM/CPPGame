#include "Camera.h"


Camera::Camera(glm::float32 near, glm::float32 far,glm::float32 width , glm::float32 height)
	:m_Near(near),m_Far(far),m_ScreenWidth(width), m_ScreenHeight(height),Component(ClassID(Camera)){
	m_CameraType = CameraType::Perspective;
	this->updateCameraMatrix();
}

Camera::Camera(CameraType type, glm::float32 width, glm::float32 height)
	:m_CameraType(type), m_ScreenWidth(width), m_ScreenHeight(height), Component(ClassID(Camera))
{}

glm::mat4 Camera::getProjectionMatrix()
{
	if(CameraType::Perspective == m_CameraType)
		return this->m_ProjectionMatrix4;
	return glm::ortho(0.0f, static_cast<GLfloat>(m_ScreenWidth), static_cast<GLfloat>(m_ScreenHeight), 0.0f, -1.0f, 1.0f);
	
}

void Camera::setNear(glm::float32 near)
{
	this->m_Near = near;
}

void Camera::setFar(glm::float32 far)
{
	this->m_Far = far;
}

void Camera::setFieldofView(glm::float32 fieldofView)
{
	this->m_FieldofView = fieldofView;
}


void Camera::updateCameraMatrix()
{
	//Í¶Ó°¾ØÕó
	m_ProjectionMatrix4 = glm::perspective(glm::radians(m_FieldofView), m_ScreenWidth / m_ScreenHeight, this->m_Near, this->m_Far);
}
