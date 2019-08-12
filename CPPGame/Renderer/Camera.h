#ifndef SRC_RENDERER_CAMERA_H
#define SRC_RENDERER_CAMERA_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraType {
	Perspective = 0,	//透视投影
	Orthographic = 1	//正交投影
};

//当前阶段的相机就是在Transform类的基础上添加上了了Near和Far，完全可以把Near和Far抽出来新建一个Camera Component
class Camera
{
public:
	glm::vec3 m_Position;		//摄像机 坐标
	glm::vec3 m_Rotation;

	glm::float32 m_Near;		//近摄像机平面距离
	glm::float32 m_Far;			//远摄像机平面距离
	glm::float32 m_FieldofView;	//相当于unity Camera 的FieldofView

	glm::float32 m_ScreenWidth;	//屏幕宽度
	glm::float32 m_ScreenHeight;	//屏幕高度

	Camera(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0,0,0), glm::float32 m_Near = 1, glm::float32 m_Far = 1000, glm::float32 width = 1280, glm::float32 height = 800);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
private:
	//			y
	//			|
	//			|
	//			|	
	//			----------->x
	//		   /
	//		  /
	//		 /
	//		z
	glm::vec3 m_Front	= glm::vec3(1, 0, 0);
	glm::vec3 m_Up		= glm::vec3(0, 1, 0);
	glm::vec3 m_Right	= glm::vec3(0, 0, 1);

	glm::mat4 m_ViewMatrix4;
	glm::mat4 m_ProjectionMatrix4;

	void updateCameraMatrix();
};
#endif //SRC_RENDERER_CAMERA_H