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
            glm::mat4 view;
            // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 3.0f));

            glm::mat4 projection;
            projection = glm::perspective<float>(glm::radians(45.0f), 800.0 / 600, 0.1f, 100.0f);
            model = glm::rotate(model, 30 * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			OpenGLDebugger::glCheckError();
            m_Shader->setMat4("projection", projection);
            OpenGLDebugger::glCheckError();
            m_Shader->setMat4("view", view);
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