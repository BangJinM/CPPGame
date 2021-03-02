#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Buffer.h"
#include "Config.h"
#include "MyMath.h"
#include "Object.h"
#include "Texture.h"

namespace GameEngine
{
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

        void AddShaderPath(ShaderType type, std::string path)
        {
            m_MapShader[type] = path;
        }

        std::string GetShaderPath(ShaderType type){
            return m_MapShader[type];
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
        std::map<ShaderType, std::string> m_MapShader;
        int shaderID = -1;
    };

    template <typename Type>
    inline void Material::AddProperty(Type value, std::string name, int size, MaterialType type)
    {
        MaterialData data(value, name, size, type);
        m_MaterialDatas.push_back(data);
    }
}  // namespace GameEngine
