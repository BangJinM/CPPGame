#include "Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"
#include "OpenGLDebugger.h"
#include "AssetManager.h"

namespace GameEngine
{
	extern AssetManager *g_pAssetManager;
	void Material::use()
	{
		m_Shader->use();
		OpenGLDebugger::glCheckError();
		for (size_t i = 0; i < m_MaterialDatas.size(); i++)
		{
			auto data = m_MaterialDatas[i];

			switch (data.type)
			{
			case MaterialType::Mat4:
			{
				auto property = (float *)data.buffer;
				m_Shader->setMat4(data.name, &property[0]);
				OpenGLDebugger::glCheckError();
				break;
			}
			case MaterialType::Texture:
			{
				auto property = (char *)data.buffer;
				OpenGLDebugger::glCheckError();
				unsigned int location;
				location = glGetUniformLocation(m_Shader->ID, data.name.c_str());
				if (location != -1)
				{
					Image* image = g_pAssetManager->getImage(property);
					m_Shader->setInt(data.name, 0);
					OpenGLDebugger::glCheckError();
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, image->id);
					OpenGLDebugger::glCheckError();
				}
				OpenGLDebugger::glCheckError();
				break;
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