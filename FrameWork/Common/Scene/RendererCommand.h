#ifndef GameEngine_Common_Scene_RendererCommand_H
#define GameEngine_Common_Scene_RendererCommand_H

#include "Component.h"
namespace GameEngine
{
    class RendererCommand : public Component
    {
    public:
        RendererCommand(ClassIDType classType) : Component(classType) {}
        virtual void excecute() = 0;

    private:
        RendererCommand() : Component(ClassID(RendererCommand)) {}
    };
} // namespace GameEngine
#endif