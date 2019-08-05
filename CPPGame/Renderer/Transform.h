#ifndef __SRC_RENDERER_TRANSFORM_H__
#define __SRC_RENDERER_TRANSFORM_H__
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.h"

class Transform :public Component
{
public:
	GameObject* m_Host; //寄主
	void SetLocalRotation(const glm::qua<float>& rotation);

	void SetLocalPosition(const glm::vec3& position);

	void SetLocalScale(const glm::vec3& scale);

	void sendTransformChange();

	Transform(const glm::vec3& position = glm::vec3(0, 0, 0), const glm::qua<float>& rotation = glm::qua<float>(0, 0, 0, 0), const glm::vec3& scale = glm::vec3(1, 1, 1));
	~Transform();
public:
	glm::vec3 m_LocalPosition, m_LocalScale; //位置，旋转，缩放
	glm::qua<float> m_LocalRotation;
};

#endif
