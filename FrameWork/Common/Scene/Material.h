#pragma once

#include "Texture.h"
#include "ShaderData.h"
#include "Buffer.h"
#include "MyMath.h"
#include "Config.h"
#include "MyMath.h"
#include "Object.h"

#include <map>
#include <vector>
#include <string>
#include <memory>

GameEngineBegin

    struct ViewUniforms
{
    static constexpr const char *VIEW_MATRIX = "u_view_matrix";
    static constexpr const char *PROJECTION_MATRIX = "u_projection_matrix";
    static constexpr const char *CAMERA_POS = "u_camera_pos";
    static constexpr const char *TIME = "u_time";

    GlmMat4 view_matrix;
    GlmMat4 projection_matrix;
    vecterFloat4 camera_pos;
    vecterFloat4 time;
};

// per renderer uniforms, set by renderer
struct RendererUniforms
{
    static constexpr const char *MODEL_MATRIX = "u_model_matrix";
    static constexpr const char *BOUNDS_MATRIX = "u_bounds_matrix";
    static constexpr const char *BOUNDS_COLOR = "u_bounds_color";
    static constexpr const char *LIGHTMAP_SCALE_OFFSET = "u_lightmap_scale_offset";
    static constexpr const char *LIGHTMAP_INDEX = "u_lightmap_index";

    GlmMat4 model_matrix;
};

enum MaterialType
{
    T_Unknown = -1,
    T_Texture,
    T_Float,
    T_Mat4,
};

struct NMaterialData
{
    std::string name;
    MaterialType type;
    char *buffer;
    int size;
};

class Material : public Object
{
public:
    static SharedMaterial createMaterial()
    {
        return std::make_shared<Material>();
    }

	Material():Object(){}

    Material(const Material &other):Object(other) {
        for (size_t i = 0; i < other.m_MaterialDatas.size(); i++)
        {
            AddProperty(other.m_MaterialDatas[i].buffer, other.m_MaterialDatas[i].name, other.m_MaterialDatas[i].size, other.m_MaterialDatas[i].type);
        }
        vert = other.vert;
        frag = other.frag;
    }
public:
    ~Material()
    {
        Clear();
    }

    void Clear()
    {
        for (size_t i = 0; i < m_MaterialDatas.size(); i++)
        {
            delete[] m_MaterialDatas[i].buffer;
        }
        m_MaterialDatas.clear();
    }

    template <typename Type>
    void AddProperty(Type value, std::string name, int size, MaterialType type);

    std::vector<NMaterialData> m_MaterialDatas;

    ShaderData frag;
    ShaderData vert;
};

template <typename Type>
inline void Material::AddProperty(Type value, std::string name, int size, MaterialType type)
{
    NMaterialData data;
    data.name = name;
    data.buffer = new char[size + 1];
    memcpy(data.buffer, value, size);
    data.buffer[size] = '\0';
    data.size = size;
    data.type = type;
    m_MaterialDatas.push_back(data);
}
GameEngineEnd
