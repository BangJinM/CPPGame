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
    class Widget : public Component
    {
    private:
        /* data */
        std::weak_ptr<CanvasRenderer> m_CanvasRenderer;
        MeshData m_MeshData;

        vecterFloat3 color[4];
        vecterFloat3 position[4];
        vecterFloat2 textcoord[4];

        MeshData& getDefaultData();
        void setDefaultData();

    public:
        Widget(/* args */);
        ~Widget();

        virtual void Start();
        virtual void InitComponent(std::shared_ptr<GameObject> host);

        std::shared_ptr<CanvasRenderer> getCanvasRenderer();
        void setCanvasRenderer(std::shared_ptr<CanvasRenderer> canvasRenderer);

        void setDefaultMesh();
    };
} // namespace GameEngine