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
        SharedMesh GetMesh() { return m_Mesh; }
        void SetMesh(SharedMesh mesh) { m_Mesh = mesh; }
        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;
    protected:
        SharedMesh m_Mesh;
        std::string m_MeshPath;
    };
}  // namespace GameEngine