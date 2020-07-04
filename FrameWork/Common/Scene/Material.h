#ifndef CPPGAME_Common_Scene_Material_H
#define CPPGAME_Common_Scene_Material_H

#include "MyMath.h"
#include "Component.h"

#include <map>
#include <vector>
#include <string>

#include "Shader.h"
#include "Buffer.h"

namespace GameEngine
{

    struct NTextureData
    {
        enum class Usage
        {
            Unknown = 0,
            None = 1,
            Diffuse = 2,
            Emissive = 3,
            Ambient = 4,
            Specular = 5,
            Shininess = 6,
            Normal = 7,
            Bump = 8,
            Transparency = 9,
            Reflection = 10
        };
        std::string id;
        std::string filename;
        Usage type;
        GLenum wrapS;
        GLenum wrapT;
    };

    enum MaterialType
    {
        Unknown = -1,
        Texture,
        Float,
        Mat4,
    };

    struct NMaterialData
    {

        std::string name;
        MaterialType type;
        Buffer* buffer;
        int size;
    };
    class Material : public Component
    {
    public:
        Material() : Component(ClassID(Material))
        {
            m_Shader = nullptr;
        }
        Material(Material *material) : Component(ClassID(Material))
        {
            m_Shader = material->m_Shader;
        }
        ~Material()
        {
            //for (size_t i = 0; i < m_MaterialDatas.size(); i++)
            //{
            //    delete( m_MaterialDatas[i].buffer);
            //}
            m_MaterialDatas.clear();
        }

        template <typename Type>
        void AddProperty(Type value, std::string name, int size, MaterialType type);

        void use();

        void setShader(Shader *shader);

        std::vector<NMaterialData> m_MaterialDatas;

        Shader *m_Shader;
    };
    template <typename Type>
    inline void Material::AddProperty(Type value, std::string name, int size, MaterialType type)
    {
        NMaterialData data;
        data.name = name;
        data.buffer = new Buffer(size + 1);
        data.buffer->m_pData[size] = '\0';

        memcpy(data.buffer->m_pData, value, size);
        data.size = size;
        data.type = type;
        m_MaterialDatas.push_back(data);
    }
} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
