#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Buffer.h"
#include "Config.h"
#include "MyMath.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"

namespace GameEngine
{
    struct ViewUniforms
    {
        static constexpr const char *VIEW_MATRIX = "u_view_matrix";
        static constexpr const char *PROJECTION_MATRIX = "u_projection_matrix";
        static constexpr const char *CAMERA_POS = "u_camera_pos";
        static constexpr const char *TIME = "u_time";

        GlmMat4 view_matrix;
        GlmMat4 projection_matrix;
        VecterFloat4 camera_pos;
        VecterFloat4 time;
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

    class MaterialData
    {
    public:
        std::string m_Name;
        MaterialType m_Type;
        Buffer *m_Buffer = nullptr;
        int m_Size;

        MaterialData()
        {
            m_Name = "";
            m_Size = 0;
            m_Type = T_Unknown;
        }

        template <typename Type>
        MaterialData(Type value, std::string name, int size, MaterialType type)
        {
            AddData(value, name, size, type);
        }

        ~MaterialData()
        {
            delete m_Buffer;
        }
        template <typename Type>
        void AddData(Type value, std::string name, int size, MaterialType type)
        {
            if (m_Buffer != nullptr)
            {
                delete m_Buffer;
                m_Buffer = nullptr;
            }
            m_Name = name;
            m_Buffer = new Buffer(size + 1);
            memcpy(m_Buffer->m_pData, value, size);
            m_Buffer->m_pData[size] = '\0';
            m_Size = size;
            m_Type = type;
        }

        MaterialData(const MaterialData &other)
        {
            AddData(other.m_Buffer->GetData(), other.m_Name, other.m_Size, other.m_Type);
        }

        MaterialData &operator=(const MaterialData &other)
        {
            if (this != &other)
            {
                AddData(other.m_Buffer->GetData(), other.m_Name, other.m_Size, other.m_Type);
            }
            return *this;
        }
    };

    class Material : public Object
    {
    public:
        static SharedMaterial createMaterial()
        {
            return std::make_shared<Material>();
        }

        Material() : Object() {}

        Material(const Material &other) : Object()
        {
            m_MaterialDatas = other.m_MaterialDatas;
            shaderID = other.shaderID;
        }

        Material &operator=(const Material &other)
        {
            if (this != &other)
            {
                m_MaterialDatas = other.m_MaterialDatas;
                shaderID = other.shaderID;
            }
            return *this;
        }

        void AddPropertys(std::vector<MaterialData> datas)
        {
            for (auto data : datas)
            {
                AddProperty(data.m_Buffer->GetData(), data.m_Name, data.m_Size, data.m_Type);
            }
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

        std::vector<MaterialData> m_MaterialDatas;

        int shaderID;
    };

    template <typename Type>
    inline void Material::AddProperty(Type value, std::string name, int size, MaterialType type)
    {
        MaterialData data(value, name, size, type);
        m_MaterialDatas.push_back(data);
    }
}  // namespace GameEngine
