#pragma once

#include <memory>
#include <string>

#include "Config.h"
#include "GameObject.h"
#include "ObjLoader.h"

GameEngineBegin 

class Scene;
class ISceneParser
{
public:
    virtual GameObject *Parse(std::string modelPath, std::string materialPath) = 0;
};

GameEngineEnd
