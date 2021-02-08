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
    extern SceneManager* g_pSceneManager;

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

        Light(LightType lightType, ClassIDType classID = ClassID(Light)) : m_LightType(lightType), Component(classID)
        {
            m_Color = ColorRGBA(1, 1, 1, 1);
        }

        Light() : m_LightType(LightType::DirectionalLight), Component(ClassID(Light))
        {
            m_Color = ColorRGBA(1, 1, 1, 1);
        }
        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "color", m_Color);
            Component::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            m_Color = SerializableHelper::DeserializeVecterFloat4(root, "color");
            Component::OnDeserialize(root);
        }

    private:
        ColorRGBA m_Color;
        LightType m_LightType;
    };

    //
    //点光源  Fatt=1.0/(Kc+Kl∗d+Kq∗d^2)
    //
    class PointLight : public Light
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            Light::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            Light::OnDeserialize(root);
        }
        PointLight(ClassIDType classID = ClassID(PointLight)) : Light(LightType::PointLight, classID) {}

        //
        // Kc 常数项
        //
        float constant;

        //
        // d 一次方项
        //
        float linear;

        //
        // d^2 二次方项
        //
        float quadratic;
    };

    class AreaLight : public Light
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            Light::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            Light::OnDeserialize(root);
        }
        AreaLight(ClassIDType classID = ClassID(AreaLight)) : Light(LightType::AreaLight, classID) {}
    };

    class SpotLight : public Light
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            Light::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            Light::OnDeserialize(root);
        }
        SpotLight(ClassIDType classID = ClassID(SpotLight)) : Light(LightType::SpotLight, classID) {}
    };

    class DirectionalLight : public Light
    {
    public:
        DirectionalLight(ClassIDType classID = ClassID(DirectionalLight)) : Light(LightType::DirectionalLight, classID) {}
        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "Ambient", m_Ambient);
            SerializableHelper::Seserialize(root, "Diffuse", m_Diffuse);
            SerializableHelper::Seserialize(root, "Specular", m_Specular);
            Light::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            Light::OnDeserialize(root);
            m_Ambient = SerializableHelper::DeserializeVecterFloat3(root, "Ambient");
            m_Diffuse = SerializableHelper::DeserializeVecterFloat3(root, "Diffuse");
            m_Specular = SerializableHelper::DeserializeVecterFloat3(root, "Specular");
        }

        //
        //环境(Ambient)
        //
        VecterFloat3 m_Ambient;

        //
        //漫反射(Diffuse)
        //
        VecterFloat3 m_Diffuse;

        //
        //镜面(Specular)光照
        //
        VecterFloat3 m_Specular;
    };

}  // namespace GameEngine