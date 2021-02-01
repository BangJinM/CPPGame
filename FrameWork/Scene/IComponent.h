#pragma once

#include "Config.h"

namespace GameEngine
{
    class IComponent
    {
    public:
        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void Destory() = 0;
    };

}  // namespace GameEngine