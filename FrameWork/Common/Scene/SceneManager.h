#ifndef GameEngine_Common_Scene_SceneManager_H
#define GameEngine_Common_Scene_SceneManager_H

#include "IRuntimeModule.h"
namespace GameEngine
{

    class SceneManager : public IRuntimeModule
    {
    public:
        virtual ~SceneManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

    private:

    };

} // namespace GameEngine

#endif