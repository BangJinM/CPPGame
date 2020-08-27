#pragma once

#include "Component.h"
#include "MyMath.h"
#include <list>
#include <vector>
#include "Mesh.h"
namespace GameEngine
{
    class CanvasRenderer;
    struct MeshData;
    class Material;
    class Widget : public Component
    {
    private:
        /* data */
        std::weak_ptr<CanvasRenderer> m_CanvasRenderer;
        std::shared_ptr<Material> m_Material;
        MeshData m_MeshData;

        vecterFloat3 color[4];
        vecterFloat3 position[4];
        vecterFloat2 textcoord[4];

        MeshData getDefaultData();

    public:
        Widget(/* args */);
        ~Widget();

		std::shared_ptr<Material> GetMaterial();
        MeshData GetMeshData();

        virtual void Start();
        virtual void InitComponent(std::shared_ptr<GameObject> host);

        std::shared_ptr<CanvasRenderer> getCanvasRenderer();
        void setCanvasRenderer(std::shared_ptr<CanvasRenderer> canvasRenderer);

        void initDefaultMesh();
        void initMaterial();
    };
} // namespace GameEngine