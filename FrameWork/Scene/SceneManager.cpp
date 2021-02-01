#include "SceneManager.h"

#include "Scene.h"

namespace GameEngine
{
    void
    SceneManager::SetNextScene(SharePtr<Scene> scene)
    {
        nextScene = scene;
    }

    SharePtr<Scene> SceneManager::GetScene()
    {
        if (curScene)
            return curScene;
        return std::make_shared<Scene>();
    }

    int SceneManager::Initialize()
    {
        curScene = std::make_shared<Scene>();
        nextScene = nullptr;
        return 0;
    }

    void SceneManager::Finalize()
    {
        curScene = nullptr;
        nextScene = nullptr;
    }

    void SceneManager::Tick()
    {
        if (!curScene)
            nextScene = std::make_shared<Scene>();
        if (nextScene)
        {
            curScene = nextScene;
            curScene->Start();
            nextScene = nullptr;
            return;
        }
        curScene->Update();
    }
}  // namespace GameEngine