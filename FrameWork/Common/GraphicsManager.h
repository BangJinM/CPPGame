#pragma once
#include "IRuntimeModule.h"
#include <vector>
#include "RendererCommand.h"
namespace GameEngine
{
    class Scene;
    class GraphicsManager : public IRuntimeModule
    {
    public:
        virtual ~GraphicsManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();
        virtual void Draw();
        virtual void Clear();

        void addRendererCommand(RendererCommand *command);
    private:
        std::vector<RendererCommand *> m_RendererCommands;

        Scene* m_Scene;
    };

    extern GraphicsManager *g_pGraphicsManager;
} // namespace GameEngine
