#pragma once

#include "Config.h"
#include "BaseGraphicsManager.h"

GameEngineBegin

class MeshData;
class Material;

class GraphicsManager : public BaseGraphicsManager
{

public:
    virtual ~GraphicsManager() {}

    virtual int Initialize();
    virtual void Finalize();

    virtual void Tick();
    virtual void Clear();

    virtual void Draw();

    void PrepareMesh(GameEngine::MeshData &meshData);
    void PrepareMaterial(GameEngine::Material &material);
};

GameEngineEnd