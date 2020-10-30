#pragma once
#include <string>

#include "Config.h"
#include "Object.h"

GameEngineBegin

using namespace std;

enum MeshValueType {
    /**Index 0 will be used as Position.*/
    VERTEX_ATTRIB_POSITION,
    /**Index 1 will be used as Color.*/
    VERTEX_ATTRIB_COLOR,
    /**Index 2 will be used as Tex coord unit 0.*/
    VERTEX_ATTRIB_TEX_COORD,
    /**Index 3 will be used as Tex coord unit 1.*/
    VERTEX_ATTRIB_TEX_COORD1,
    /**Index 4 will be used as Tex coord unit 2.*/
    VERTEX_ATTRIB_TEX_COORD2,
    /**Index 5 will be used as Tex coord unit 3.*/
    VERTEX_ATTRIB_TEX_COORD3,
    /**Index 6 will be used as Normal.*/
    VERTEX_ATTRIB_NORMAL,
    /**Index 7 will be used as Blend weight for hardware skin.*/
    VERTEX_ATTRIB_BLEND_WEIGHT,
    /**Index 8 will be used as Blend index.*/
    VERTEX_ATTRIB_BLEND_INDEX,
    /**Index 9 will be used as tangent.*/
    VERTEX_ATTRIB_TANGENT,
    /**Index 10 will be used as Binormal.*/
    VERTEX_ATTRIB_BINORMAL,
    VERTEX_ATTRIB_MAX,

    // backward compatibility
    VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
};

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