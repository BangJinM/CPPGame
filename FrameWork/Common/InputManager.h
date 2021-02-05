#pragma once

#include <functional>
#include <list>
#include <map>

#include "Config.h"
#include "IRuntimeModule.h"

namespace GameEngine
{
    class InputManager;
    extern InputManager *g_pInputManager;
    class InputManager : public IRuntimeModule
    {
        typedef std::function<void()> CallBack;
        struct GameEngineCallBack
        {
            std::list<CallBack> *callbacks;

            GameEngineCallBack() { callbacks = new std::list<CallBack>(); }

            void push(CallBack callback) { callbacks->push_back(callback); }

            void remove(CallBack callback)
            {
                auto iter = callbacks->begin();
                // while (iter != callbacks->end())
                //{

                //}
            }

            void dispatch()
            {
                auto iter = callbacks->begin();
                while (iter != callbacks->end())
                {
                    CallBack callback = *iter;
                    (callback)();
                    ++iter;
                }
            }
        };

    public:
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick(float deltaTime);

        static void addClickEventListener(const char key, CallBack callBack);

        static void removeClickEventListener(const char key, CallBack callBack);

        static void dispatchClickEvent(const char key);

    private:
        /* data */
        std::map<char, GameEngineCallBack *> _listeners;
    };
}  // namespace GameEngine
