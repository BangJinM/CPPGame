﻿#include "Config.h"
#include "OpenGLCoinfig.h"
#include "Windows/WindowsConfig.h"
#include "GfxConfiguration.h"
#include "Windows/GamePlatform-opengl.h"
#include "MyGameLogic.h"
namespace GameEngine
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540);
    IApplication *g_pApp = static_cast<IApplication *>(new OpenGLApplication(config));
    GameLogic *g_pGameLogic = static_cast<GameLogic *>(new MyGameLogic);
} // namespace GameEngine