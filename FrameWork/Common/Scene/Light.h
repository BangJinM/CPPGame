#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Config.h"
#include "MyMath.h"
#include "Component.h"
#include "Transform.h"

GameEngineBegin 

class Light : public Component
{
public:
    enum LightType
    {
        PointLight = 0,
        AreaLight,
        SpotLight,
        DirectionalLight
    };

public:
    Light(LightType lightType) : m_LightType(lightType), Component(ClassID(Light))
    {
        m_Color = vecterFloat3(1, 1, 1);
    }

    Light() : m_LightType(LightType::DirectionalLight), Component(ClassID(Light))
    {
        m_Color = vecterFloat3(1, 1, 1);
    }

private:
    vecterFloat3 m_Color;
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
};

GameEngineEnd