#ifndef GameEngine_InputManager_H
#define GameEngine_InputManager_H

#include "IRuntimeModule.h"
#include <list>
#include <map>

namespace GameEngine{
    class InputManager :IRuntimeModule
    {
        public:
            virtual int Initialize();
            virtual void Finalize();
            virtual void Tick();

            void addClickEventListener(const char key, void* func);

            void removeClickEventListener(const char key, void *func);

            void dispatchClickEvent(const char key);

        private:
            /* data */
            std::map<char, std::list<void*>> _listeners;
    };
    extern InputManager* g_pInputManager;
}
#endif