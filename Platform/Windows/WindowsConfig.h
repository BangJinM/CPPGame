#pragma once

#include "MemoryManager.h"
#include "InputManager.h"
#include "InputManagerWindows.h"
#include "AssetLoader.h"
#include "AssetManager.h"
#include "ParserManager.h"
#include "SceneManager.h"

namespace GameEngine
{
    MemoryManager *g_pMemoryManager = static_cast<MemoryManager *>(new MemoryManager);
    InputManager *g_pInputManager = static_cast<InputManagerWindows *>(new InputManagerWindows);
    GameEngineFile::AssetLoader *g_pAssetLoader = static_cast<GameEngineFile::AssetLoader *>(new GameEngineFile::AssetLoader);
    AssetManager *g_pAssetManager = static_cast<AssetManager *>(new AssetManager);
    GameEngineParser::ParserManager *g_pParserManager = static_cast<GameEngineParser::ParserManager *>(new GameEngineParser::ParserManager);
    SceneManager *g_pSceneManager = static_cast<SceneManager *>(new SceneManager);
} // namespace GameEngine