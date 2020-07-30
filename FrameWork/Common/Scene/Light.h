#ifndef CPPGAME_Common_Scene_Light_H
#define CPPGAME_Common_Scene_Light_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MyMath.h"
#include "Component.h"
#include "Transform.h"
namespace GameEngine
{
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
        Light(ClassIDType classID, LightType lightType):m_LightType(lightType), Component(classID){}

    private:
        vecterFloat3 color;
        LightType m_LightType;
    };

    class PointLight :public Light{
        PointLight():Light(ClassID(PointLight), LightType::PointLight){}
    };

    class AreaLight :public Light{
        AreaLight():Light(ClassID(PointLight), LightType::AreaLight){}
    };

    class SpotLight :public Light{
        SpotLight():Light(ClassID(PointLight), LightType::SpotLight){}
    };

    class DirectionalLight :public Light{
        DirectionalLight():Light(ClassID(PointLight), LightType::DirectionalLight){}
    };

} // namespace GameEngine
#endif //SRC_RENDERER_LIGHT_H