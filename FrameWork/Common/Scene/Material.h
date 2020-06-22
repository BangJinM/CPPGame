#ifndef CPPGAME_Common_Scene_Material_H
#define CPPGAME_Common_Scene_Material_H

#include "MyMath.h"
#include "Component.h"

#include <map>
#include <vector>
#include <string>

#include "Shader.h"

namespace GameEngine
{

    class Material : public Component
    {
	public:
        Material() : Component(ClassID(Material))
        {

        }
        ~Material() {}

        Shader *shader;
    };
} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
