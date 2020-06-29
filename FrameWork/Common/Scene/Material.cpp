#include "Material.h"
namespace GameEngine
{
    void Material::use()
    {
    }

    void Material::setShader(Shader *shader) {
        m_Shader = shader;
    }
} // namespace GameEngine