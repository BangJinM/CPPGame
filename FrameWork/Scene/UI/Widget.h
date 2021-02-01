#pragma once

#include <list>
#include <vector>

#include "Component.h"
#include "Config.h"
#include "Mesh.h"
#include "MyMath.h"

namespace GameEngine
{
    class CanvasRenderer;
    class MeshData;
    class Material;
    class Widget : public Component
    {
    private:
        /* data */
        std::weak_ptr<CanvasRenderer> m_CanvasRenderer;
        SharedMaterial m_Material;

    public:
        Widget(/* args */);
        ~Widget();

        SharedMaterial GetMaterial();
        MeshData GetMeshData();

        virtual void Start();
        virtual void InitComponent(SharedGameObject host);

        SharePtr<CanvasRenderer> getCanvasRenderer();
        void setCanvasRenderer(SharePtr<CanvasRenderer> canvasRenderer);
    };
}  // namespace GameEngine