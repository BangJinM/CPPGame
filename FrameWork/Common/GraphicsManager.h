#pragma once

#include <vector>

#include "Config.h"
#include "Renderer.h"
#include "IRuntimeModule.h"

GameEngineBegin

class Scene;
class GraphicsManager : public IRuntimeModule
{
public:
    virtual ~GraphicsManager() {}

    virtual int Initialize();
    virtual void Finalize();

    virtual void Tick();
    virtual void Clear();

    void addRendererCommand(SharePtr<Renderer> command);

private:
    std::vector<SharePtr<Renderer>> m_RendererCommands;
};

extern GraphicsManager *g_pGraphicsManager;
GameEngineEnd
