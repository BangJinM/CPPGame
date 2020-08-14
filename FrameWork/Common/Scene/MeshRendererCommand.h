#ifndef GameEngine_Common_Scene_MeshRendererCommand_H
#define GameEngine_Common_Scene_MeshRendererCommand_H

#include "RendererCommand.h"
#include "MyMath.h"
#include "Mesh.h"
#include <glad/glad.h>
#include "Material.h"
#include "OpenGLDebugger.h"
namespace GameEngine
{
	class MeshRendererCommand : public RendererCommand
	{
	public:
		MeshRendererCommand()
		{
			material = nullptr;
		}

		virtual ~MeshRendererCommand()
		{
		}

		virtual void excecute()
		{
			if (material && material->m_Shader.ID > 0)
				material->use();
			glBindVertexArray(m_Vao);
			glDrawElements(m_Mode, m_Count, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			OpenGLDebugger::glCheckError();
		}

	public:
		std::shared_ptr<Material> material;
		GLuint m_Vao;
		GLenum m_Mode;
		GLenum m_Yype;
		GLsizei m_Count;
	};
} // namespace GameEngine
#endif