#ifndef GameEngine_Common_Scene_Renderer_H
#define GameEngine_Common_Scene_Renderer_H

#include "MyMath.h"
#include <list>
#include "Component.h"

namespace GameEngine
{
    class Renderer : public Component
    {
    public:
        static void Draw();
        Renderer();
    private:
        static std::list<Renderer*> m_renderers;
    };
} // namespace GameEngine
#endif