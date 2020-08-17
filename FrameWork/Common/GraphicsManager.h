#pragma once
#include "IRuntimeModule.h"
#include <vector>
#include "Renderer.h"
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
        virtual void Clear();

        void addRendererCommand(std::shared_ptr<Renderer> command);

    private:
        std::vector<std::shared_ptr<Renderer>> m_RendererCommands;

        std::shared_ptr<Scene> m_Scene;
    };

    extern GraphicsManager *g_pGraphicsManager;
} // namespace GameEngine
