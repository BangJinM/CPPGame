#pragma once

#include "AssetLoader.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "InputManagerWindows.h"
#include "MemoryManager.h"
#include "ParserManager.h"
#include "SceneManager.h"

namespace GameEngine
{
    MemoryManager *g_pMemoryManager = static_cast<MemoryManager *>(new MemoryManager);
    InputManager *g_pInputManager = static_cast<InputManagerWindows *>(new InputManagerWindows);
    AssetLoader *g_pAssetLoader = static_cast<AssetLoader *>(new AssetLoader);
    AssetManager *g_pAssetManager = static_cast<AssetManager *>(new AssetManager);
    ParserManager *g_pParserManager = static_cast<ParserManager *>(new ParserManager);
    SceneManager *g_pSceneManager = static_cast<SceneManager *>(new SceneManager);
}  // namespace GameEngine