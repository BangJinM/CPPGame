#ifndef __SRC_RENDERER_TRANSFORM_H__
#define __SRC_RENDERER_TRANSFORM_H__
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.h"

class Transform :public Component
{
public:
	
	void SetLocalRotation(const glm::vec3& rotation);

	void SetLocalPosition(const glm::vec3& position);

	void SetLocalScale(const glm::vec3& scale);

	void SetLocalAnchor(const glm::vec3& anchor);

	void sendTransformChange();

	glm::mat4 getTransformMatrix4();

	Transform(
		const glm::vec3& position = glm::vec3(0, 0, 0), 
		const glm::vec3& rotation = glm::vec3(0, 0, 0), 
		const glm::vec3& scale = glm::vec3(1, 1, 1)
	);
	~Transform();
public:
	glm::vec3 m_LocalPosition, m_LocalRotation, m_LocalScale, m_Anchor; //位置，旋转，缩放，锚点
};

#endif
