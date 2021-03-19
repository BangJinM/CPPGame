#pragma once

#include "AssetLoader.h"
#include "AssetManager.h"
#include "Event/EventDispatcherManager.h"
#include "InputManager.h"
#include "MemoryManager.h"
#include "OpenGLShaderManager.h"
#include "Render/GraphicsManager.h"
#include "SceneManager.h"
#include "SpecialModuleConfig.h"
#include "Utils/Clock.h"

namespace GameEngine
{
    MemoryManager *g_pMemoryManager = static_cast<MemoryManager *>(new MemoryManager);
    InputManager *g_pInputManager = static_cast<InputManager *>(new InputManager);
    AssetLoader *g_pAssetLoader = static_cast<AssetLoader *>(new AssetLoader);
    AssetManager *g_pAssetManager = static_cast<AssetManager *>(new AssetManager);
    Clock *g_pClock = static_cast<Clock *>(new Clock);
    SceneManager *g_pSceneManager = static_cast<SceneManager *>(new SceneManager);
    GraphicsManager *g_pGraphicsManager = static_cast<GraphicsManager *>(new GraphicsManager);

}  // namespace GameEngine

namespace EventSystem
{
    EventDispatcherManager *g_pEventDispatcherManager = static_cast<EventDispatcherManager *>(new EventDispatcherManager);
}