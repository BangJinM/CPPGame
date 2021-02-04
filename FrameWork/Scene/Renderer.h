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

        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;

    protected:
        std::vector<std::string> m_MaterialPaths;
        std::vector<SharedMaterial> m_Materials;
    };
}  // namespace GameEngine
