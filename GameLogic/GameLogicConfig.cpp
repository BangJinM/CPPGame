#include "Config.h"
#include "GfxConfiguration.h"
#include "ModuleConfig.h"
#include "MyGameLogic.h"

namespace GameEngine
{
    GameLogic *g_pGameLogic = static_cast<GameLogic *>(new MyGameLogic);
}  // namespace GameEngine