#pragma once

#include "Config.h"
#include "Mesh.h"
#include "Renderer.h"

namespace GameEngine
{
    class Camera;
    class MeshRenderer : public Renderer
    {
    public:
        MeshRenderer();
        SharedMesh getMesh() { return m_Mesh; }
        void SetMesh(SharedMesh mesh) { m_Mesh = mesh; }
        virtual void Render(SharePtr<Camera> camera);

    protected:
        SharedMesh m_Mesh;
    };
}  // namespace GameEngine