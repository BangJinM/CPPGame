#ifndef GameEngine_Common_Scene_MeshRenderer_H
#define GameEngine_Common_Scene_MeshRenderer_H

#include "Renderer.h"
#include "Mesh.h"

namespace GameEngine
{
    class MeshRenderer : public Renderer
    {
    public:
        MeshRenderer();
        void Draw();
        std::shared_ptr<Mesh> getMesh(){return m_Mesh;}
        void SetMesh(std::shared_ptr<Mesh> mesh){ m_Mesh = mesh;}
    private:
        std::shared_ptr<Mesh> m_Mesh;
    };
} // namespace GameEngine
#endif