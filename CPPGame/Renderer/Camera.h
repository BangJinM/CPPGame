#ifndef SRC_RENDERER_CAMERA_H
#define SRC_RENDERER_CAMERA_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraType {
	Perspective = 0,	//͸��ͶӰ
	Orthographic = 1	//����ͶӰ
};

//��ǰ�׶ε����������Transform��Ļ��������������Near��Far����ȫ���԰�Near��Far������½�һ��Camera Component
class Camera
{
public:
	glm::vec3 m_Position;		//����� ����
	glm::vec3 m_Rotation;

	glm::float32 m_Near;		//�������ƽ�����
	glm::float32 m_Far;			//Զ�����ƽ�����
	glm::float32 m_FieldofView;	//�൱��unity Camera ��FieldofView

	glm::float32 m_ScreenWidth;	//��Ļ���
	glm::float32 m_ScreenHeight;	//��Ļ�߶�

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