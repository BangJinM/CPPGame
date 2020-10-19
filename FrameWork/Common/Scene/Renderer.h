#pragma once

#include <list>
#include <vector>

#include "MyMath.h"
#include "Component.h"

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
		std::shared_ptr<Mesh> getMesh();// { return std::shared_ptr<Mesh>(); }
		std::vector<std::shared_ptr<Material>> getMaterials();// { return m_Materials; }
		void AddMaterial(std::shared_ptr<Material> material);// { m_Materials.push_back(material); }
		virtual void Render(std::shared_ptr<Camera> camera);// {}
        virtual void Start();
    protected:
        std::vector<std::shared_ptr<Material>> m_Materials;
    };
} // namespace GameEngine
