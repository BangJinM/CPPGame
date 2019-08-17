#ifndef SRC_RENDERER_CAMERA_H
#define SRC_RENDERER_CAMERA_H

#include <glad/glad.h>
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraType {
	Perspective = 0,	//透视投影
	Orthographic = 1	//正交投影
};

//Camera Component
class Camera :public Component
{
public:

	glm::float32 m_Near;		//近摄像机平面距离
	glm::float32 m_Far;			//远摄像机平面距离
	glm::float32 m_FieldofView;	//相当于unity Camera 的FieldofView

	glm::float32 m_ScreenWidth;	//屏幕宽度
	glm::float32 m_ScreenHeight;	//屏幕高度

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