#include "Config.h"
#include "GfxConfiguration.h"
#include "MyGameLogic.h"
#include "OpenGLCoinfig.h"
#include "Windows/GamePlatform-opengl.h"
#include "Windows/WindowsConfig.h"
namespace GameEngine
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540);
    BaseApplication *g_pApp = static_cast<BaseApplication *>(new OpenGLApplication(config));
    GameLogic *g_pGameLogic = static_cast<GameLogic *>(new MyGameLogic);
}  // namespace GameEngine