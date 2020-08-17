#ifndef CPPGAME_Common_Scene_Material_H
#define CPPGAME_Common_Scene_Material_H

#include "MyMath.h"
#include "Object.h"

#include <map>
#include <vector>
#include <string>

#include "Image.h"
#include "Shader.h"
#include "Buffer.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define _DEBUG
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DBG_NEW new
#endif

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
        char *buffer;
        int size;
    };
    class Material : public Object
    {
    public:
        static std::shared_ptr<Material> createMaterial()
        {
            return std::make_shared<Material>();
        }
        static std::shared_ptr<Material> createMaterial(std::shared_ptr<Material> material1)
        {
            std::shared_ptr<Material> material = Material::createMaterial();
            material->setMaterial(material1);
            return material;
        }

        Material()
        {
        }

    private:
        void setMaterial(std::shared_ptr<Material> material)
        {
            m_Shader = material->m_Shader;
            Clear();
            for (size_t i = 0; i < material->m_MaterialDatas.size(); i++)
            {
                AddProperty(material->m_MaterialDatas[i].buffer, material->m_MaterialDatas[i].name, material->m_MaterialDatas[i].size, material->m_MaterialDatas[i].type);
            }
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

        void use();

        void setShader(Shader& shader);

        std::vector<NMaterialData> m_MaterialDatas;

        Shader m_Shader;
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
} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
