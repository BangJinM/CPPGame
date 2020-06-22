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
	struct NMaterialData
	{
		std::vector<NTextureData> textures;
		std::string id;
		const NTextureData *getTextureData(const NTextureData::Usage &type) const
		{
			for (const auto &it : textures)
			{
				if (it.type == type)
					return &it;
			}
			return nullptr;
		}
	};
    class Material : public Component
    {
    public:
        Material(Shader *shader) : Component(ClassID(Material))
        {
            m_Shader = shader;
        }
        ~Material() {}

        Shader *m_Shader;
    };
} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
