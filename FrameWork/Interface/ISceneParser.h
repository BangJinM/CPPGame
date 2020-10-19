#pragma once

#include <memory>
#include <string>
#include "GameObject.h"
#include "ObjLoader.h"
namespace GameEngine
{
    class Scene;
    class ISceneParser
    {
    public:
        virtual GameObject *Parse(std::string modelPath, std::string materialPath) = 0;
    };
} // namespace GameEngine
