#include "Transform.h"

void Transform::SetLocalRotation(const glm::qua<float>& rotation){
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

void Transform::sendTransformChange(){

}

Transform::Transform(const glm::vec3& position, const glm::qua<float>& rotation , const glm::vec3& scale)
	:m_LocalPosition(position),m_LocalRotation(rotation),m_LocalScale(scale),Component(ClassID(Transform)) {
}

Transform::~Transform() {

}