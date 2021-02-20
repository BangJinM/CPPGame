#include "BaseGraphicsManager.h"

#include <algorithm>
#include <iostream>

#include "AssetLoader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Render/Draw/ForwardDrawPass.h"
#include "Scene.h"
#include "Light.h"
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
            viewInfos.u_camera_pos = cameraTs->GetPosition();
            viewInfos.u_projection_matrix = camera->getProjectionMatrix();
            viewInfos.u_view_matrix = cameraTs->GetMatrix();

            for (auto render : scene->m_Renderers)
            {
                render->Render(viewInfos);
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
		for (auto iter = lights.begin(); iter !=lights.end(); iter++)
		{
			index++;
			auto light = *iter;
			m_LightInfos.lights[index].type = light->GetLightType();

			auto transfrom = light->GetParent()->getComponent<Transform>();
			auto pos = transfrom->GetPosition();
			auto rotation = transfrom->GetRotation();

			m_LightInfos.lights[index].color = light->GetColor();
			m_LightInfos.lights[index].position = VecterFloat4(pos, 0);
			m_LightInfos.lights[index].direction = VecterFloat4(rotation, 0);

			auto directionalLight = std::dynamic_pointer_cast<DirectionalLight>(light);
			m_LightInfos.lights[index].ambient = VecterFloat4(directionalLight->GetAmbient(),0);
			m_LightInfos.lights[index].diffuse = VecterFloat4(directionalLight->GetDiffuse(), 0);
			m_LightInfos.lights[index].specular = VecterFloat4(directionalLight->GetSpecular(), 0);
			if (m_LightInfos.lights[index].type == LightType::Type_DirectionalLight)
				continue;

			auto pointLight = std::dynamic_pointer_cast<PointLight>(light);
			m_LightInfos.lights[index].constant = pointLight->GetConstant();
			m_LightInfos.lights[index].linear = pointLight->GetLinear();
			m_LightInfos.lights[index].quadratic = pointLight->GetQuadratic();
			if (m_LightInfos.lights[index].type == LightType::Type_PointLight)
				continue;

			auto spotLight = std::dynamic_pointer_cast<SpotLight>(light);
			m_LightInfos.lights[index].cutOff = spotLight->GetCutOff();
			m_LightInfos.lights[index].outerCutOff = spotLight->GetOuterCutOff();
			if (m_LightInfos.lights[index].type == LightType::Type_SpotLight)
				continue;
		}
    }

}  // namespace GameEngine
