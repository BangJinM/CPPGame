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

class NMaterialData
{
public:
    std::string m_Name;
    MaterialType  m_Type;
    char * m_Buffer;
    int  m_Size;
    template <typename Type>
    NMaterialData(Type value, std::string name, int size, MaterialType type){
		m_Name = name;
		m_Buffer = new char[size + 1];
        memcpy(m_Buffer, value, size);
		m_Buffer[size] = '\0';
		m_Size = size;
		m_Type = type;
    }
    
    NMaterialData(const NMaterialData &data) {
		m_Name = data.m_Name;
		m_Buffer = new char[data.m_Size + 1];
        memcpy(m_Buffer, data.m_Buffer, data.m_Size);
		m_Buffer[data.m_Size] = '\0';
		m_Size = data.m_Size;
		m_Type = data.m_Type;
    }

	~NMaterialData() {
		delete m_Buffer;
	}
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
            AddProperty(other.m_MaterialDatas[i].m_Buffer, other.m_MaterialDatas[i].m_Name, other.m_MaterialDatas[i].m_Size, other.m_MaterialDatas[i].m_Type);
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
    NMaterialData data(value, name, size, type);
    m_MaterialDatas.push_back(data);
}
GameEngineEnd
