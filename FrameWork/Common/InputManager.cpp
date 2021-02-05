#include "InputManager.h"

#include <utility>

namespace GameEngine
{
    int InputManager::Initialize() { return 0; }

    void InputManager::Finalize() {}

    void InputManager::Tick(float deltaTime) {}

    void InputManager::addClickEventListener(const char key, CallBack callBack)
    {
        auto iter = g_pInputManager->_listeners.find(key);

        if (iter == g_pInputManager->_listeners.end())
        {
            GameEngineCallBack *list = new GameEngineCallBack();
            g_pInputManager->_listeners.insert(
                std::pair<char, GameEngineCallBack *>(key, list));
            addClickEventListener(key, callBack);
            return;
        }
        iter->second->push(callBack);
    }

    void InputManager::removeClickEventListener(char key, CallBack callBack)
    {
        auto iter = g_pInputManager->_listeners.find(key);
        if (iter != g_pInputManager->_listeners.end())
        {
            iter->second->remove(callBack);
        }
    }

    //
    void InputManager::dispatchClickEvent(char key)
    {
        auto iter = g_pInputManager->_listeners.find(key);
        int i = 0;
        if (iter != g_pInputManager->_listeners.end())
        {
            iter->second->dispatch();
        }
    }
}  // namespace GameEngine