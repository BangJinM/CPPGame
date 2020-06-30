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
        enum MaterialType{
            Unknown = -1,
            Texture, 
            Num,
        };
        std::string name;
        MaterialType type;
        char * data;
        int size;
    };
    class Material : public Component
    {
    public:
        Material() : Component(ClassID(Material))
        {
            m_Shader = nullptr;
        }
        ~Material() {
            m_MaterialDatas.clear();
        }

        void use(GlmMat4 viewMat, GlmMat4 projectMat, GlmMat4 model);

        void setShader(Shader *shader);

        std::vector<NMaterialData> m_MaterialDatas;

        Shader *m_Shader;
    };
} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
