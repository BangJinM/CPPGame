#include "Camera.h"

#include "BaseApplication.h"
#include "GameObject.h"
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
        auto camera = GetParent()->GetComponent<Camera>();
        if (!camera)
            return;
        auto scene = g_pSceneManager->GetScene();
        scene->AddCamera(std::dynamic_pointer_cast<Camera>(camera));
    }

    glm::mat4 Camera::GetProjectionMatrixOrthographic()
    {
        return m_ProjectionMatrix4_Orthographic;
    }

    Frustum Camera::CalculateFrustum(float fNear, float fFar)
    {
        auto trans = GetParent()->GetComponent<Transform>();
        glm::vec3 center = trans->GetPosition();
        glm::vec3 view_dir = trans->GetForward();

        glm::vec3 rightT = trans->GetRight();
        glm::vec3 upT = trans->GetUp();

        glm::vec3 vFarPlaneCenter = center + view_dir * fFar;
        glm::vec3 vNearPlaneCenter = center + view_dir * fNear;

        float ratio = m_ScreenWidth / m_ScreenHeight;
        float fov = m_FieldofView / 180 * glm::pi<float>();

        float fNearPlaneHalfHeight = tan(fov / 2.0f) * fNear;
        float fNearPlaneHalfWidth = fNearPlaneHalfHeight * ratio;

        float fFarPlaneHalfHeight = tan(fov / 2.0f) * fFar;
        float fFarPlaneHalfWidth = fFarPlaneHalfHeight * ratio;

        Frustum frustum;

        frustum.m_pPoints[0] = vNearPlaneCenter - rightT * fNearPlaneHalfHeight - upT * fNearPlaneHalfWidth;
        frustum.m_pPoints[1] = vNearPlaneCenter + rightT * fNearPlaneHalfHeight - upT * fNearPlaneHalfWidth;
        frustum.m_pPoints[2] = vNearPlaneCenter + rightT * fNearPlaneHalfHeight + upT * fNearPlaneHalfWidth;
        frustum.m_pPoints[3] = vNearPlaneCenter - rightT * fNearPlaneHalfHeight + upT * fNearPlaneHalfWidth;

        frustum.m_pPoints[4] = vFarPlaneCenter - rightT * fFarPlaneHalfHeight - upT * fFarPlaneHalfWidth;
        frustum.m_pPoints[5] = vFarPlaneCenter + rightT * fFarPlaneHalfHeight - upT * fFarPlaneHalfWidth;
        frustum.m_pPoints[6] = vFarPlaneCenter + rightT * fFarPlaneHalfHeight + upT * fFarPlaneHalfWidth;
        frustum.m_pPoints[7] = vFarPlaneCenter - rightT * fFarPlaneHalfHeight + upT * fFarPlaneHalfWidth;

        frustum.CalculateAABB();
        return frustum;
    }

    void Camera::CalculateSplitPositions(float *pDistances, int numSplits)
    {
        float lambda = 0.75;
        float ratio = m_Far / m_Near;
        pDistances[0] = m_Near;

        for (int i = 1; i < numSplits; i++)
        {
            float si = i / (float)numSplits;
            float t_near = lambda * (m_Near * powf(ratio, si)) + (1 - lambda) * (m_Near + (m_Far - m_Near) * si);
            pDistances[i] = t_near;
        }
        pDistances[numSplits] = m_Far;
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