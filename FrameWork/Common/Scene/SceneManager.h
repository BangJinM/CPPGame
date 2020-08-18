#ifndef GameEngine_Common_Scene_SceneManager_H
#define GameEngine_Common_Scene_SceneManager_H

#include "IRuntimeModule.h"
#include <list>
#include "Camera.h"
#include "Renderer.h"
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