#include "Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"
#include "OpenGLDebugger.h"
namespace GameEngine
{
    void Material::use(GlmMat4 viewMat, GlmMat4 projectMat, GlmMat4 model)
    {
        if (m_Shader != nullptr)
        {
            OpenGLDebugger::glCheckError();
            m_Shader->use();
			OpenGLDebugger::glCheckError();
            m_Shader->setMat4("projection", projectMat);
            OpenGLDebugger::glCheckError();
            m_Shader->setMat4("view", viewMat);
            OpenGLDebugger::glCheckError();
            m_Shader->setMat4("model", model);
            OpenGLDebugger::glCheckError();
        }
    }

    void Material::setShader(Shader *shader)
    {
        m_Shader = shader;
    }
} // namespace GameEngine