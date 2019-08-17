#include "Transform.h"
#include <glm/gtc/quaternion.hpp>

void Transform::SetLocalRotation(const glm::vec3& rotation){
	m_LocalRotation = rotation;
	sendTransformChange();
}

void Transform::SetLocalPosition(const glm::vec3& position) {
	m_LocalPosition = position;
	sendTransformChange();
}

void Transform::SetLocalScale(const glm::vec3& scale) {
	m_LocalScale = scale;
	sendTransformChange();
}

void Transform::SetLocalAnchor(const glm::vec3 & anchor)
{
	m_Anchor = anchor;
	sendTransformChange();
}

void Transform::sendTransformChange(){

}

glm::mat4 Transform::getTransformMatrix4()
{
	glm::mat4 model = glm::mat4(1);

	//Æ½ÒÆ
	model = glm::translate(model, this->m_LocalPosition);
	//Ðý×ª
	glm::qua<float> quaternion = glm::qua<float>(glm::radians(this->m_LocalRotation));
	model = model * glm::mat4_cast(quaternion);
	//Ëõ·Å
	model = glm::scale(model, this->m_LocalScale); // Last scale

	return model;
}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation , const glm::vec3& scale)
	:m_LocalPosition(position),m_LocalRotation(rotation),m_LocalScale(scale),Component(ClassID(Transform)) {
}

Transform::~Transform() {

}