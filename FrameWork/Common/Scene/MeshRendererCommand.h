#ifndef GameEngine_Common_Scene_MeshRendererCommand_H
#define GameEngine_Common_Scene_MeshRendererCommand_H

#include "RendererCommand.h"
#include "MyMath.h"
#include "Mesh.h"
#include <glad/glad.h>
namespace GameEngine
{
    class Material;
    class MeshRendererCommand : public RendererCommand
    {
    public:

        MeshRendererCommand();

		~MeshRendererCommand();

		virtual void excecute();

    private:

        Material *m_MaterailID;
        // Mesh * m_Mesh;
        
        GLuint m_Vao;
        GLenum m_Mode;
        GLenum m_Yype;
        GLsizei m_Count;
		Matrix4X4f m_Transform;
    };
} // namespace GameEngine
#endif