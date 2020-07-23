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
					m_Shader->setInt(data.name, getTextureID(image));
				}
				OpenGLDebugger::glCheckError();
				break;
			}
			default:
				break;
			}
		}
	}

	int Material::getTextureID(Image * image)
	{
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Ϊ��ǰ�󶨵������������û��ơ����˷�ʽ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (image)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->Width, image->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			printf("Failed to load texture");
		}
		return texture;
	}

	

	void Material::setShader(Shader *shader)
	{
		m_Shader = shader;
	}
} // namespace GameEngine