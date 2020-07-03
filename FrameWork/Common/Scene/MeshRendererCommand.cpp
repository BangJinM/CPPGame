#include "MeshRendererCommand.h"
#include "OpenGLDebugger.h"
namespace GameEngine
{

    MeshRendererCommand::MeshRendererCommand()
    {
		material = nullptr;
    }

    MeshRendererCommand::~MeshRendererCommand()
    {
    }

    void MeshRendererCommand::excecute()
    {
		if(material)
			material->use();
        glBindVertexArray(m_Vao);
        glDrawElements(m_Mode, m_Count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        OpenGLDebugger::glCheckError();
    }

} // namespace GameEngine