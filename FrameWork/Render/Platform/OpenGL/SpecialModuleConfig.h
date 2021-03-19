#pragma once

#include "OpenGLApplication.h"
#include "OpenGLShaderManager.h"

namespace GameEngine
{
    ShaderManager *g_pShaderManager = static_cast<ShaderManager *>(new OpenGLShaderManager);
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540);
    BaseApplication *g_pApp = static_cast<BaseApplication *>(new OpenGLApplication(config));
}  // namespace GameEngine