#pragma once

#include "Mesh.h"
#include "Config.h"
#include "Renderer.h"

GameEngineBegin 

class Camera;
class MeshRenderer : public Renderer
{
public:
    MeshRenderer();
    SharedMesh getMesh() { return m_Mesh; }
    void SetMesh(SharedMesh mesh) { m_Mesh = mesh; }
    virtual void Render(SharePtr<Camera> camera);

protected:
    SharedMesh m_Mesh;
};
GameEngineEnd