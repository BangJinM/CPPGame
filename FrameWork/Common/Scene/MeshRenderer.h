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
    private:
        std::shared_ptr<Mesh> m_mesh;
    };
} // namespace GameEngine
#endif