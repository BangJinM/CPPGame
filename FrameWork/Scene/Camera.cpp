#include "Camera.h"

#include "BaseApplication.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Utils/SerializableHelper.h"

namespace GameEngine
{
    extern BaseApplication *g_pApp;
    extern SceneManager *g_pSceneManager;

    Camera::Camera(glm::float32 width, glm::float32 height, glm::float32 near,
                   glm::float32 far, glm::float32 fieldofView, ClassIDType classID)
        : m_Near(near), m_Far(far), m_ScreenWidth(width), m_ScreenHeight(height), m_FieldofView(fieldofView)
    {
        m_ProjectionMatrix4_Perspective = glm::perspective(
            glm::radians(m_FieldofView), m_ScreenWidth / m_ScreenHeight, this->m_Near,
            this->m_Far);
        m_ProjectionMatrix4_Orthographic = glm::ortho(0.0f, width, height, 0.0f);
        m_ClassID = ClassID(Camera);
    }

    Camera::Camera(glm::float32 near, glm::float32 far, glm::float32 fieldofView, ClassIDType classID)
        : m_Near(near), m_Far(far), m_FieldofView(fieldofView)
    {
        auto config = g_pApp->GetGfxConfiguration();
        m_ScreenHeight = (float)config.screenHeight;
        m_ScreenWidth = (float)config.screenWidth;
        m_ProjectionMatrix4_Perspective = glm::perspective(
            glm::radians(m_FieldofView), m_ScreenWidth / m_ScreenHeight, this->m_Near,
            this->m_Far);
        // glm::orthographic
        m_ProjectionMatrix4_Orthographic =
            glm::ortho(0.0f, m_ScreenWidth, m_ScreenHeight, 0.0f);
        m_ClassID = ClassID(Camera);
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        return this->m_ProjectionMatrix4_Perspective;
    }

    void Camera::SetProjectionMatrix(glm::mat4 temp)
    {
        this->m_ProjectionMatrix4_Perspective = temp;
    }

    void Camera::Start()
    {
        Component::Start();
        auto camera = GetParent()->getComponent<Camera>();
        if (!camera)
            return;
        auto scene = g_pSceneManager->GetScene();
        scene->AddCamera(std::dynamic_pointer_cast<Camera>(camera));
    }

    glm::mat4 Camera::GetProjectionMatrixOrthographic()
    {
        return m_ProjectionMatrix4_Orthographic;
    }

    void Camera::OnSerialize(cJSON *root)
    {
        Component::OnSerialize(root);
    }

    void Camera::OnDeserialize(cJSON *root)
    {
        Component::OnDeserialize(root);
    }
}  // namespace GameEngine