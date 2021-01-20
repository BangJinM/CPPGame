#pragma once

#include <memory>

#include "Config.h"

GameEngineBegin 

class Scene;
class SceneManager
{

private:
    static SharePtr<SceneManager> m_SceneManager;

public:
    static SharePtr<SceneManager> GetInstance();

private:
    SceneManager(/* args */);
    SharePtr<Scene> curScene;
    SharePtr<Scene> nextScene;

public:
    void SetNextScene(SharePtr<Scene> scene);
    void ChangeScene();
    void Update();
    SharePtr<Scene> GetScene();
    ~SceneManager();
};
GameEngineEnd