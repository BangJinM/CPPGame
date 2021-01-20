#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

GameEngineBegin

Transform::Transform() : Component(ClassID(Transform))
{
	m_Position = vecterFloat3(0, 0, 0);
	m_Scale = vecterFloat3(1, 1, 1);
	m_Rotation = vecterFloat3(0, 0, 0);
	m_Matrix = GlmMat4(1.0f);
	setMatrix(m_Position, m_Scale, m_Rotation);
}

void Transform::setPosition(vecterFloat3 position)
{
	m_Position = position;
	setMatrix(m_Position, m_Scale, m_Rotation);
}
void Transform::setScale(vecterFloat3 scale)
{
	m_Scale = scale;
	setMatrix(m_Position, m_Scale, m_Rotation);
}
void Transform::setRotation(vecterFloat3 rotation)
{

	m_Rotation = rotation;
	setMatrix(m_Position, m_Scale, m_Rotation);
}
void Transform::setMatrix(vecterFloat3 position, vecterFloat3 scale, vecterFloat3 rotation)
{
	m_Matrix = GlmMat4(1.0f);
	m_Matrix = glm::translate(m_Matrix, position);
	m_Matrix = glm::scale(m_Matrix, scale);
	glm::qua<float> q = glm::qua<float>(glm::radians(rotation)); //创建一个四元数
	m_Matrix = glm::mat4_cast(q) * m_Matrix;					 //得到一个旋转的模型矩阵
}
GameEngineEnd
