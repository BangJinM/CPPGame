#include "Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"
#include "OpenGLDebugger.h"
namespace GameEngine
{
	void Material::use()
    {
		m_Shader->use();
		for (size_t i = 0; i < m_MaterialDatas.size(); i++)
		{
			auto data = m_MaterialDatas[i];

			switch (data.type)
			{
			case MaterialType::Mat4:
			{
				auto property = (float *)data.buffer->m_pData;
				m_Shader->setMat4(data.name, &property[0]);
			}
			default:
				break;
			}
		}
    }

    void Material::setShader(Shader *shader)
    {
        m_Shader = shader;
    }
} // namespace GameEngine