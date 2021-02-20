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
    enum LightType
    {
        Type_PointLight = 1,
        Type_AreaLight,
        Type_SpotLight,
        Type_DirectionalLight
    };
    class Light : public Component
    {
    public:
        virtual void Start() override
        {
            Component::Start();
            auto light = GetParent()->getComponent<Light>();
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

        Light()
        {
            m_Color = ColorRGBA(1, 1, 1, 1);
            m_ClassID = ClassID(Light);
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

        int GetLightType() { return m_LightType; }

        ColorRGBA GetColor() { return m_Color; }

    protected:
        /////////////////////////////////
        //光颜色
        /////////////////////////////////
        ColorRGBA m_Color;
        /////////////////////////////////
        // 光类型
        /////////////////////////////////
        LightType m_LightType;
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
        AreaLight()
        {
            m_ClassID = ClassID(AreaLight);
            m_LightType = LightType::Type_AreaLight;
        }
    };
    /////////////////////////////////
    //方向光
    /////////////////////////////////
    class DirectionalLight : public Light
    {
    public:
        DirectionalLight()
        {
            m_ClassID = ClassID(DirectionalLight);
            m_LightType = LightType::Type_DirectionalLight;
        }
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

        VecterFloat3 GetAmbient() { return m_Ambient; }
        VecterFloat3 GetDiffuse() { return m_Diffuse; }
        VecterFloat3 GetSpecular() { return m_Specular; }

        /////////////////////////////////
        //环境(Ambient)
        /////////////////////////////////
        VecterFloat3 m_Ambient;

        /////////////////////////////////
        //漫反射(Diffuse)
        /////////////////////////////////
        VecterFloat3 m_Diffuse;

        /////////////////////////////////
        //镜面(Specular)光照
        /////////////////////////////////
        VecterFloat3 m_Specular;
    };

    /////////////////////////////////
    //点光源  Fatt=1.0/(Kc+Kl∗d+Kq∗d^2)
    /////////////////////////////////
    class PointLight : public DirectionalLight
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "constant", constant);
            SerializableHelper::Seserialize(root, "linear", linear);
            SerializableHelper::Seserialize(root, "quadratic", quadratic);
            DirectionalLight::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            constant = SerializableHelper::DeserializeFloat(root, "constant");
            linear = SerializableHelper::DeserializeFloat(root, "linear");
            quadratic = SerializableHelper::DeserializeFloat(root, "quadratic");
            DirectionalLight::OnDeserialize(root);
        }
        PointLight()
        {
            m_ClassID = ClassID(PointLight);
            m_LightType = LightType::Type_PointLight;
        }

        float GetConstant() { return constant; }
        float GetLinear() { return linear; }
        float GetQuadratic() { return quadratic; }

	private:
        /////////////////////////////////
        // Kc 常数项
        /////////////////////////////////
        float constant;

        /////////////////////////////////
        // d 一次方项
        /////////////////////////////////
        float linear;

        /////////////////////////////////
        // d^2 二次方项
        /////////////////////////////////
        float quadratic;
    };
    /////////////////////////////////
    // 聚光灯
    /////////////////////////////////
    class SpotLight : public PointLight
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "cutOff", cutOff);
            SerializableHelper::Seserialize(root, "outerCutOff", outerCutOff);
            PointLight::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            cutOff = SerializableHelper::DeserializeFloat(root, "cutOff");
            outerCutOff = SerializableHelper::DeserializeFloat(root, "outerCutOff");
            PointLight::OnDeserialize(root);
        }
        SpotLight()
        {
            m_ClassID = ClassID(SpotLight);
            m_LightType = LightType::Type_SpotLight;
        }

        float GetCutOff() { return cutOff; }
        float GetOuterCutOff() { return outerCutOff; }

    private:
        /////////////////////////////////
        //内圆锥
        /////////////////////////////////
        float cutOff;
        /////////////////////////////////
        // 外圆锥
        /////////////////////////////////
        float outerCutOff;
    };

}  // namespace GameEngine