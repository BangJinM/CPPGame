#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Component.h"
#include "Config.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;

    class Light : public Component
    {
    public:
        enum LightType
        {
            PointLight = 1 << 1,
            AreaLight = 1 << 2,
            SpotLight = 1 << 3,
            DirectionalLight = 1 << 4
        };

    public:
        virtual void Start() override
        {
            Component::Start();
            auto light = getParent()->getComponent<Light>();
            if (!light)
                return;
            auto scene = g_pSceneManager->GetScene();
            scene->AddLight(std::dynamic_pointer_cast<Light>(light));
        }

        virtual void Update() override
        {
            Component::Update();
        }
        virtual void Destory() override
        {
            Component::Destory();
        }

        Light(LightType lightType) : m_LightType(lightType), Component(ClassID(Light))
        {
            m_Color = ColorRGBA(1, 1, 1, 1);
        }

        Light() : m_LightType(LightType::DirectionalLight), Component(ClassID(Light))
        {
            m_Color = ColorRGBA(1, 1, 1, 1);
        }

    private:
        ColorRGBA m_Color;
        LightType m_LightType;
    };

    class PointLight : public Light
    {
    public:
        PointLight() : Light(LightType::PointLight) {}
    };

    class AreaLight : public Light
    {
    public:
        AreaLight() : Light(LightType::AreaLight) {}
    };

    class SpotLight : public Light
    {
    public:
        SpotLight() : Light(LightType::SpotLight) {}
    };

    class DirectionalLight : public Light
    {
    public:
        DirectionalLight() : Light(LightType::DirectionalLight) {}

    private:
        vecterFloat3 direction;
    };

}  // namespace GameEngine