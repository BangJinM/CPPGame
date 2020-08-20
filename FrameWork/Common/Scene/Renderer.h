#ifndef GameEngine_Common_Scene_Renderer_H
#define GameEngine_Common_Scene_Renderer_H

#include "MyMath.h"
#include <list>
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
namespace GameEngine
{
    class Renderer : public Component
    {
    public:
        void Prepare();
        Renderer();
        std::shared_ptr<Mesh> getMesh() { return std::shared_ptr<Mesh>(); }
        std::vector<std::shared_ptr<Material>> getMaterials() { return m_Materials; }
        void AddMaterial(std::shared_ptr<Material> material) { m_Materials.push_back(material); }
        virtual void Render() {}

    protected:
        std::vector<std::shared_ptr<Material>> m_Materials;
        RendererUniforms m_RendererUniforms;
    };
} // namespace GameEngine
#endif