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

    void addRendererCommand(std::shared_ptr<Renderer> command);

private:
    std::vector<std::shared_ptr<Renderer>> m_RendererCommands;
};

extern GraphicsManager *g_pGraphicsManager;
GameEngineEnd
