#ifndef GameEngine_Common_SceneManager_H
#define GameEngine_Common_SceneManager_H

#include "IRuntimeModule.h"
#include <list>
#include <map>
#include <functional>

namespace GameEngine{
    class InputManager :IRuntimeModule
    {
        public:
            virtual int Initialize();
            virtual void Finalize();
            virtual void Tick();
        private:
    };
    
}
#endif