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
        SharedMesh GetMesh();                          
        std::vector<SharedMaterial> GetMaterials();   
        void AddMaterial(SharedMaterial material);    

        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;

    protected:
        std::vector<std::string> m_MaterialPaths;
        std::vector<SharedMaterial> m_Materials;
    };
}  // namespace GameEngine
