#ifndef CPPGAME_Common_Scene_Material_H
#define CPPGAME_Common_Scene_Material_H

#include "MyMath.h"
#include "Object.h"

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "Texture.h"
#include "Shader.h"
#include "Buffer.h"
#include "MyMath.h"

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
        // GlmMat4 bounds_matrix;
        //Color bounds_color;
        // vecterFloat4 lightmap_scale_offset;
        // vecterFloat4 lightmap_index; // in x
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

        void Use();

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

        void Prepare();

        void setShader(Shader &shader);

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
