#pragma once

#include "Config.h"
#include "IRuntimeModule.h"

namespace GameEngine
{
    class GameLogic : public IRuntimeModule
    {
    private:
        /* data */
    public:
    };

    extern GameLogic *g_pGameLogic;

}  // namespace GameEngine