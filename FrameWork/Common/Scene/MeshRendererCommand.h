#ifndef GameEngine_Common_Scene_MeshRendererCommand_H
#define GameEngine_Common_Scene_MeshRendererCommand_H

#include "RendererCommand.h"
#include "MyMath.h"
#include "Mesh.h"
#include <glad/glad.h>
#include "Material.h"
namespace GameEngine
{
    class MeshRendererCommand : public RendererCommand
    {
    public:
        MeshRendererCommand();

        ~MeshRendererCommand();

        virtual void excecute();

    public:

        Material *material;
        GLuint m_Vao;
        GLenum m_Mode;
        GLenum m_Yype;
        GLsizei m_Count;
    };
} // namespace GameEngine
#endif