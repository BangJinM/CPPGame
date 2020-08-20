#include "Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GLFW/glfw3.h"
#include "OpenGLDebugger.h"
#include "AssetManager.h"

namespace GameEngine
{
	extern AssetManager *g_pAssetManager;

	void Material::Use()
	{
		m_Shader.use();
	}

	void Material::Prepare()
	{
		int textureID = 0;
		m_Shader.use();
		OpenGLDebugger::glCheckError();
		for (size_t i = 0; i < m_MaterialDatas.size(); i++)
		{
			auto data = m_MaterialDatas[i];

			switch (data.type)
			{
			case MaterialType::T_Mat4:
			{
				auto property = (float *)data.buffer;
				m_Shader.setMat4(data.name, &property[0]);
				OpenGLDebugger::glCheckError();
				break;
			}
			case MaterialType::T_Texture:
			{
				auto property = (char *)data.buffer;
				OpenGLDebugger::glCheckError();
				unsigned int location;
				location = glGetUniformLocation(m_Shader.ID, data.name.c_str());
				if (location != -1)
				{
					OpenGLDebugger::glCheckError();
					std::shared_ptr<Texture> image = g_pAssetManager->LoadTexture(property);
					if (!image)
						image = g_pAssetManager->getWhiteTexture();
					m_Shader.setInt(data.name, textureID);
					OpenGLDebugger::glCheckError();
					glActiveTexture(GL_TEXTURE0 + textureID);
					glBindTexture(GL_TEXTURE_2D, image->id);
					OpenGLDebugger::glCheckError();
					textureID++;
				}
				OpenGLDebugger::glCheckError();
				break;
			}
			default:
				break;
			}
		}
	}

	void Material::setShader(Shader &shader)
	{
		m_Shader = shader;
	}
} // namespace GameEngine