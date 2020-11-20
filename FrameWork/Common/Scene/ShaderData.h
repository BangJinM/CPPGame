#pragma once
#include <string>

#include "Config.h"
#include "Object.h"

GameEngineBegin

using namespace std;

class ShaderData : public Object
{
public:
    std::string path;
	std::string value;
public:
    ShaderData() : path(""), value("")
    {
    }
    ShaderData(std::string p, std::string v) : path(p), value(v),Object() {}
};
GameEngineEnd