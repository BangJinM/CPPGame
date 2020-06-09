#ifndef GameEngine_Common_Scene_MeshRendererCommand_H
#define GameEngine_Common_Scene_MeshRendererCommand_H

#include "RendererCommand.h"
#include "MyMath.h"
#include <glad/glad.h>
namespace GameEngine
{
    class Material;
    class MeshRendererCommand : public RendererCommand
    {
    public:
        MeshRendererCommand();

    private:
        Material *m_MaterailID;
        GLuint vao;
        GLenum mode;
        GLenum type;
        GLsizei count;
		Matrix4X4f transform;
    };
} // namespace GameEngine
#endif