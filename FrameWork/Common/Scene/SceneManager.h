#ifndef GameEngine_Common_Scene_SceneManager_H
#define GameEngine_Common_Scene_SceneManager_H

#include "IRuntimeModule.h"
#include <list>
#include "Camera.h"
#include "Renderer.h"
namespace GameEngine
{

    class SceneManager : public IRuntimeModule
    {
    public:
        virtual ~SceneManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        void RenderAll();
        void AddCamera(std::shared_ptr<Camera> renderer);
        void RemoveCamera();

        void PrepareAll();
        void AddRenderer(std::shared_ptr<Renderer> renderer);
        void RemoveRenderer();
        std::list<std::shared_ptr<Renderer>> GetRenderer() { return m_renderers; }

    private:
        std::list<std::shared_ptr<Camera>> m_Cameras;
        std::list<std::shared_ptr<Renderer>> m_renderers;
    };

} // namespace GameEngine

#endif