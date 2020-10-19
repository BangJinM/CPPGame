#pragma once

#include "Renderer.h"
#include "Mesh.h"

namespace GameEngine
{
    class Camera;
    class MeshRenderer : public Renderer
    {
    public:
        MeshRenderer();
        std::shared_ptr<Mesh> getMesh() { return m_Mesh; }
        void SetMesh(std::shared_ptr<Mesh> mesh) { m_Mesh = mesh; }
        virtual void Render(std::shared_ptr<Camera> camera);

    protected:
        std::shared_ptr<Mesh> m_Mesh;
    };
} // namespace GameEngine
