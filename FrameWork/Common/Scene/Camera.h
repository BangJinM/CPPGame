#ifndef CPPGAME_Common_Scene_Camera_H
#define CPPGAME_Common_Scene_Camera_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"
#include "Transform.h"
#include "Renderer.h"
namespace GameEngine
{
    class Camera : public Component
    {
        enum CameraType
        {
            Perspective = 0, //透视投影
            Orthographic = 1 //正交投影
        };

    public:
        Camera(glm::float32 m_Near = 0.1, glm::float32 m_Far = 1000, glm::float32 width = 960, glm::float32 height = 540, glm::float32 fieldofView = 45);
        glm::mat4 getProjectionMatrix();


		void Render(std::list<std::shared_ptr<Renderer>> renderers);
        virtual void Update();
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

        glm::float32 m_Near;        //近摄像机平面距离
        glm::float32 m_Far;         //远摄像机平面距离
        glm::float32 m_FieldofView; //摄像机夹角

        glm::float32 m_ScreenWidth;  //屏幕宽度
        glm::float32 m_ScreenHeight; //屏幕高度

        glm::mat4 m_ProjectionMatrix4;

    };
} // namespace GameEngine
#endif //SRC_RENDERER_CAMERA_H