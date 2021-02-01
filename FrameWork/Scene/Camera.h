﻿#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"
#include "Config.h"
#include "Renderer.h"
#include "Transform.h"

namespace GameEngine
{
    class Camera : public Component
    {
        enum CameraType
        {
            Perspective = 0,  //透视投影
            Orthographic = 1  //正交投影
        };

    public:
        Camera(glm::float32 width, glm::float32 height, glm::float32 m_Near = 0.1,
               glm::float32 m_Far = 1000, glm::float32 fieldofView = 45);
        Camera(glm::float32 m_Near = 0.1, glm::float32 m_Far = 1000,
               glm::float32 fieldofView = 45);
        glm::mat4 getProjectionMatrix();

        virtual void Start();

        glm::mat4 getProjectionMatrixOrthographic();

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

        glm::float32 m_Near;         //近摄像机平面距离
        glm::float32 m_Far;          //远摄像机平面距离
        glm::float32 m_FieldofView;  //摄像机夹角

        glm::float32 m_ScreenWidth;   //屏幕宽度
        glm::float32 m_ScreenHeight;  //屏幕高度

        glm::mat4 m_ProjectionMatrix4_Perspective;
        glm::mat4 m_ProjectionMatrix4_Orthographic;
    };
}  // namespace GameEngine