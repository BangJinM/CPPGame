#ifndef SRC_RENDERER_CAMERA_H
#define SRC_RENDERER_CAMERA_H

#include <glad/glad.h>
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraType {
	Perspective = 0,	//͸��ͶӰ
	Orthographic = 1	//����ͶӰ
};

//Camera Component
class Camera :public Component
{
public:

	glm::float32 m_Near;		//�������ƽ�����
	glm::float32 m_Far;			//Զ�����ƽ�����
	glm::float32 m_FieldofView;	//�൱��unity Camera ��FieldofView

	glm::float32 m_ScreenWidth;	//��Ļ���
	glm::float32 m_ScreenHeight;	//��Ļ�߶�

	Camera(glm::float32 m_Near = 1, glm::float32 m_Far = 1000, glm::float32 width = 1280, glm::float32 height = 800);

	Camera(CameraType type, glm::float32 width = 1280, glm::float32 height = 800);

	glm::mat4 getProjectionMatrix();

	void setNear(glm::float32 near);
	void setFar(glm::float32 far);
	void setFieldofView(glm::float32 fieldofView);

private:
	glm::mat4 m_ProjectionMatrix4; //

	CameraType m_CameraType = CameraType::Orthographic;

	void updateCameraMatrix();
};
#endif //SRC_RENDERER_CAMERA_H