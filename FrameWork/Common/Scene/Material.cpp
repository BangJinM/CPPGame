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
            glm::mat4 view(1);
            // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 1.f));
            glm::mat4 projection(1);
			glm::mat4 model(1);
			model = glm::translate(model, vecterFloat3(0.0f, 0.0f, 0.0f));
			float scale = 1;
            projection = glm::perspective(glm::radians(90.0f), (float)960 / (float)540, 0.1f, 10000.0f);
            model = glm::rotate(model, 30 * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
			model = glm::scale(model, glm::vec3(1.f/500, 1.f/500, 1.f/500));
			auto temp = projection * view * model * vecterFloat4(0.9275293, - 0.2048915, 0.3125842, 1.0f);
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