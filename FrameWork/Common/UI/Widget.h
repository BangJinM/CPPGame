#pragma once

#include "Mesh.h"
#include "MyMath.h"
#include "Config.h"
#include "Component.h"

#include <list>
#include <vector>

GameEngineBegin

class CanvasRenderer;
struct MeshData;
class Material;
class Widget : public Component
{
private:
    /* data */
    std::weak_ptr<CanvasRenderer> m_CanvasRenderer;
    SharedMaterial m_Material;
    MeshData m_MeshData;

    vecterFloat3 color[4];
    vecterFloat3 position[4];
    vecterFloat2 textcoord[4];

    MeshData getDefaultData();

public:
    Widget(/* args */);
    ~Widget();

    SharedMaterial GetMaterial();
    MeshData GetMeshData();

    virtual void Start();
    virtual void InitComponent(SharedGameObject host);

    SharePtr<CanvasRenderer> getCanvasRenderer();
    void setCanvasRenderer(SharePtr<CanvasRenderer> canvasRenderer);

    void initDefaultMesh();
    void initMaterial();
};
GameEngineEnd