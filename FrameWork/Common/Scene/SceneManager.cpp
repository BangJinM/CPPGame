#include "SceneManager.h"

namespace GameEngine
{
    void SceneManager::RenderAll()
    {
        for (auto i = m_Cameras.begin(); i != m_Cameras.end(); i++)
        {
            auto renderers = GetRenderer();
            (*i)->Render(renderers);
        }
    }

    void SceneManager::RemoveCamera()
    {
    }
    void SceneManager::AddCamera(std::shared_ptr<Camera> renderer)
    {
    }

    void SceneManager::PrepareAll()
    {
        for (auto i = m_renderers.begin(); i != m_renderers.end(); i++)
        {
            (*i)->Prepare();
        }
    }
    void SceneManager::AddRenderer(std::shared_ptr<Renderer> renderer)
    {
        m_renderers.push_back(renderer);
    }
    void SceneManager::RemoveRenderer()
    {
    }
} // namespace GameEngine