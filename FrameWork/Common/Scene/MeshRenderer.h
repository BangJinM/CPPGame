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
    std::shared_ptr<Mesh> getMesh() { return m_Mesh; }
    void SetMesh(std::shared_ptr<Mesh> mesh) { m_Mesh = mesh; }
    virtual void Render(std::shared_ptr<Camera> camera);

protected:
    std::shared_ptr<Mesh> m_Mesh;
};
GameEngineEnd