#include "Transform.h"
namespace GameEngine
{
	Transform::Transform() : Component(ClassID(Transform))
	{
		m_Position = vecterFloat3(0, 0, 0);
		m_Scale = vecterFloat3(1, 1, 1);
		m_Rotation = vecterFloat3(0, 0, 0);
		setMatrix(m_Position, m_Rotation, m_Scale);
	}

	void Transform::setPosition(vecterFloat3 position)
	{
		m_Position = position;
		setMatrix(m_Position, m_Rotation, m_Scale);
	}
	void Transform::setScale(vecterFloat3 scale)
	{
		m_Scale = scale;
		setMatrix(m_Position, m_Rotation, m_Scale);
	}
	void Transform::setRotation(vecterFloat3 rotation)
	{
		m_Rotation = rotation;
		setMatrix(m_Position, m_Rotation, m_Scale);
	}
	void Transform::setMatrix(vecterFloat3 position, vecterFloat3 scale, vecterFloat3 rotation)
	{
		m_Matrix = {
			position.x, position.y,position.z,m_Matrix[3],
			rotation.x,rotation.y,rotation.z,m_Matrix[7],
			scale.x,scale.y,scale.z,m_Matrix[11],
			m_Matrix[12],m_Matrix[13],m_Matrix[14],m_Matrix[15],
		};
	}
} // namespace GameEngine

