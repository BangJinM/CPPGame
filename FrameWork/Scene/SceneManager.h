#pragma once

#include <memory>

#include "Config.h"
#include "IRuntimeModule.h"

namespace GameEngine
{
    class Scene;
    class SceneManager : public IRuntimeModule
    {
    private:
        SharePtr<Scene> curScene;
        SharePtr<Scene> nextScene;

    public:
        void SetNextScene(SharePtr<Scene> scene);

        SharePtr<Scene> GetScene();

        virtual int Initialize() override;

        virtual void Finalize() override;

        virtual void Tick(float deltaTime) override;
    };

    extern SceneManager *g_pSceneManager;
}  // namespace GameEngine