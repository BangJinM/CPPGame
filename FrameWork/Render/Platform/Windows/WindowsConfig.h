#pragma once

#include "AssetLoader.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "InputManagerWindows.h"
#include "MemoryManager.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "OpenGLShaderManager.h"
#include "Utils/Clock.h"

namespace GameEngine
{
    MemoryManager *g_pMemoryManager = static_cast<MemoryManager *>(new MemoryManager);
    InputManager *g_pInputManager = static_cast<InputManagerWindows *>(new InputManagerWindows);
    AssetLoader *g_pAssetLoader = static_cast<AssetLoader *>(new AssetLoader);
    AssetManager *g_pAssetManager = static_cast<AssetManager *>(new AssetManager);
    Clock *g_pClock = static_cast<Clock *>(new Clock);
    SceneManager *g_pSceneManager = static_cast<SceneManager *>(new SceneManager);
    BaseGraphicsManager *g_pGraphicsManager = static_cast<GraphicsManager *>(new GraphicsManager);
    ShaderManager *g_pShaderManager = static_cast<ShaderManager *>(new OpenGLShaderManager);
}  // namespace GameEngine