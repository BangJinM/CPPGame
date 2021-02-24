#include "BaseGraphicsManager.h"

#include <algorithm>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "AssetLoader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "Render/Draw/ForwardDrawPass.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
using namespace std;

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    extern AssetLoader *g_pAssetLoader;

    int BaseGraphicsManager::Initialize()
    {
        m_IDrawPass.push_back(std::make_shared<ForwardDrawPass>());
        for (auto pass : m_IDrawPass)
        {
            pass->Initialize();
        }
        return 0;
    }

    void BaseGraphicsManager::Finalize() {}

    void BaseGraphicsManager::Clear() { m_RendererCommands.clear(); }

    void BaseGraphicsManager::Draw()
    {
        for (auto pass : m_IDrawPass)
        {
            pass->Draw();
        }
    }

    void BaseGraphicsManager::Tick(float deltaTime)
    {
        auto scene = g_pSceneManager->GetScene();
        CalculateLights();
        SetLightInfo(m_LightInfos);
        for (auto camera : scene->m_Cameras)
        {
            auto cameraTs = camera->GetParent()->getComponent<Transform>();
            ViewInfos viewInfos;
            memcpy(viewInfos.u_camera_pos, glm::value_ptr(cameraTs->GetPosition()), sizeof(float) * 3);
            memcpy(viewInfos.u_projection_matrix, glm::value_ptr(camera->getProjectionMatrix()), sizeof(float) * 16);
            memcpy(viewInfos.u_view_matrix, glm::value_ptr(cameraTs->GetMatrix()), sizeof(float) * 16);

            SetViewInfos(viewInfos);
            for (auto render : scene->m_Renderers)
            {
                render->Render();
            }
        }
        Draw();
        m_RendererCommands.clear();
    }

    void BaseGraphicsManager::addRendererCommand(RendererCammand command)
    {
        m_RendererCommands.push_back(command);
    }

    std::list<RendererCammand> BaseGraphicsManager::getRendererCommand()
    {
        return m_RendererCommands;
    }

    void BaseGraphicsManager::CalculateLights()
    {
        auto scene = g_pSceneManager->GetScene();
        auto lights = scene->GetLights();
        m_LightInfos.numsLight = lights.size();
        int index = -1;
        for (auto iter = lights.begin(); iter != lights.end(); iter++)
        {
            index++;
            auto light = *iter;
            m_LightInfos.lights[index].type = light->GetLightType();

            auto transfrom = light->GetParent()->getComponent<Transform>();
            auto pos = transfrom->GetPosition();
            auto dir = transfrom->GetMatrix() * VecterFloat4(1, 0, 0, 0);
            
            memcpy(m_LightInfos.lights[index].color, glm::value_ptr(light->GetColor()), sizeof(float) * 4);
            memcpy(m_LightInfos.lights[index].position, glm::value_ptr(pos), sizeof(float) * 3);
            memcpy(m_LightInfos.lights[index].direction, glm::value_ptr(dir), sizeof(float) * 3);

            auto directionalLight = std::dynamic_pointer_cast<DirectionalLight>(light);
            memcpy(m_LightInfos.lights[index].ambient, glm::value_ptr(directionalLight->GetAmbient()), sizeof(float) * 3);
            memcpy(m_LightInfos.lights[index].diffuse, glm::value_ptr(directionalLight->GetDiffuse()), sizeof(float) * 3);
            memcpy(m_LightInfos.lights[index].specular, glm::value_ptr(directionalLight->GetSpecular()), sizeof(float) * 3);
            if (m_LightInfos.lights[index].type == LightType::Type_DirectionalLight)
                continue;

            auto pointLight = std::dynamic_pointer_cast<PointLight>(light);
            m_LightInfos.lights[index].constant = pointLight->GetConstant();
            m_LightInfos.lights[index].linear = pointLight->GetLinear();
            m_LightInfos.lights[index].quadratic = pointLight->GetQuadratic();
            if (m_LightInfos.lights[index].type == LightType::Type_PointLight)
                continue;

            auto spotLight = std::dynamic_pointer_cast<SpotLight>(light);
            m_LightInfos.lights[index].cutOff = glm::cos(glm::radians(spotLight->GetCutOff()));
            m_LightInfos.lights[index].outerCutOff = glm::cos(glm::radians(spotLight->GetOuterCutOff()));
            if (m_LightInfos.lights[index].type == LightType::Type_SpotLight)
                continue;
        }
    }

}  // namespace GameEngine