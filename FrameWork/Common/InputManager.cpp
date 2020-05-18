
#include "InputManager.h"

int GameEngine::InputManager::Initialize()
{
    return 0;
}

void GameEngine::InputManager::Finalize()
{
}

void GameEngine::InputManager::Tick()
{
}

void GameEngine::InputManager::addClickEventListener(const char key, void *func)
{
    auto funs =  _listeners.find(key);
}

void GameEngine::InputManager::removeClickEventListener(char key, void *func)
{
}

void GameEngine::InputManager::dispatchClickEvent(char key)
{
}
