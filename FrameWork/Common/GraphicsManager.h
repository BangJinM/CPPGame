#pragma once
#include "IRuntimeModule.h"
#include <vector>
#include "RendererCommand.h"
namespace GameEngine
{
    class GameObject;
    class GraphicsManager : public IRuntimeModule
    {
    public:
        virtual ~GraphicsManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();
        virtual void Draw();
        virtual void Clear();

    private:
        std::vector<RendererCommand> m_RendererCommands;

        GameObject *gameobject;
        GameObject *cameraObject;
    };

    extern GraphicsManager *g_pGraphicsManager;
} // namespace GameEngine
