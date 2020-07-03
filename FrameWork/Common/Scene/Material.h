#ifndef CPPGAME_Common_Scene_Material_H
#define CPPGAME_Common_Scene_Material_H

#include "MyMath.h"
#include "Component.h"

#include <map>
#include <vector>
#include <string>

#include "Shader.h"

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
		Vec3,
		Mat4,
	};

    struct NMaterialData
    {
        
        std::string name;
        MaterialType type;
        void *data;
        int size;
    };
    class Material : public Component
    {
    public:
        Material() : Component(ClassID(Material))
        {
            m_Shader = nullptr;
        }
		Material(Material * material) : Component(ClassID(Material))
		{
			m_Shader = material->m_Shader;
			m_MaterialDatas = material->m_MaterialDatas;
		}
        ~Material()
        {
            m_MaterialDatas.clear();
        }

		template <typename Type>
        void AddProperty(Type value, std::string name, MaterialType type);

        void use();

        void setShader(Shader *shader);

        std::vector<NMaterialData *> m_MaterialDatas;

        Shader *m_Shader;
    };
	template<typename Type>
	inline void Material::AddProperty(Type value, std::string name, MaterialType type)
	{
		NMaterialData* data = new NMaterialData();
		data->name = name;
		data->data = &value;
		auto temp = (GlmMat4 *)data->data;
		data->type = type;
		m_MaterialDatas.push_back(data);
	}
} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
