#pragma once

#include <memory>

namespace GameEngine
{
    class Scene;
    class SceneManager
    {

    private:
        static std::shared_ptr<SceneManager> m_SceneManager;

    public:
        static std::shared_ptr<SceneManager> GetInstance();

    private:
        SceneManager(/* args */);
        std::shared_ptr<Scene> curScene;
        std::shared_ptr<Scene> nextScene;

    public:
        void SetNextScene(std::shared_ptr<Scene> scene);
        void ChangeScene();
        void Update();
        std::shared_ptr<Scene> GetScene();
        ~SceneManager();
    };
} // namespace GameEngine