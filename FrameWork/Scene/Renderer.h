#pragma once

#include <list>
#include <vector>

#include "Component.h"
#include "Config.h"
#include "MyMath.h"

namespace GameEngine
{
    class Camera;
    class Material;
    class Mesh;
    class Renderer : public Component
    {
    public:
        void Prepare();
        Renderer();
        SharedMesh getMesh();                          // { return SharedMesh(); }
        std::vector<SharedMaterial> getMaterials();    // { return m_Materials; }
        void AddMaterial(SharedMaterial material);     // { m_Materials.push_back(material); }
        virtual void Render(SharePtr<Camera> camera);  // {}
        virtual void Start();

    protected:
        std::vector<SharedMaterial> m_Materials;
    };
}  // namespace GameEngine
