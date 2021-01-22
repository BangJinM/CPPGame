#pragma once

#include <list>

#include "Config.h"
#include "IRuntimeModule.h"
#include "Renderer.h"

#include "../Renderer/Frame.h"
#include "Material.h"
#include "Mesh.h"
GameEngineBegin

    class Scene;

class BaseGraphicsManager : public IRuntimeModule
{
public:
    virtual ~BaseGraphicsManager() {}

    virtual int Initialize();
    virtual void Finalize();

    virtual void Tick();
    virtual void Clear();
    virtual void Draw();

    void addRendererCommand(RendererCammand command);
    std::list<RendererCammand> getRendererCommand();

protected:
    std::list<RendererCammand> m_RendererCommands;
};

extern BaseGraphicsManager *g_pGraphicsManager;
GameEngineEnd
