﻿#include "IApplication.h"
#include "MemoryManager.h"
#include "InputManager.h"
#include "../File/AssetLoader.h"
#include "BaseGraphicsManager.h"
#include "AssetManager.h"
using namespace GameEngine;

namespace GameEngine
{
	extern IApplication *g_pApp;
	extern MemoryManager *g_pMemoryManager;
	extern InputManager *g_pInputManager;
	extern GameEngineFile::AssetLoader *g_pAssetLoader;
	extern BaseGraphicsManager *g_pGraphicsManager;
	extern AssetManager *g_pAssetManager;

} // namespace GameEngine

int main(int argc, char *argv[])
{

	for (int i = 0; i < argc; i++)
		printf(argv[i]);

	int ret;

	if ((ret = g_pApp->Initialize()) != 0)
	{
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pMemoryManager->Initialize()) != 0)
	{
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pInputManager->Initialize()) != 0)
	{
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pAssetLoader->Initialize()) != 0)
	{
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret = g_pAssetManager->Initialize()) != 0)
	{
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	if ((ret == g_pGraphicsManager->Initialize()) != 0)
	{
		printf("App Initialize failed, will exit now.");
		return ret;
	}
	int i = 1;
	while (!g_pApp->IsQuit())
	{
//#ifdef WIN32
//	_CrtMemState s1, s2, s3;
//	_CrtMemCheckpoint(&s1);
//#endif // DEBUG

		g_pMemoryManager->Tick();
		g_pInputManager->Tick();
		g_pAssetLoader->Tick();
		g_pAssetManager->Tick();
		g_pGraphicsManager->Tick();
		g_pApp->Tick();
//#ifdef WIN32
//		_CrtMemCheckpoint(&s2);
//		if (_CrtMemDifference(&s3, &s1, &s2))
//			_CrtMemDumpStatistics(&s3);
//		_CrtDumpMemoryLeaks();
//#endif // DEBUG
	}


	g_pGraphicsManager->Finalize();
	g_pInputManager->Finalize();
	g_pAssetLoader->Finalize();
	g_pAssetManager->Finalize();
	g_pMemoryManager->Finalize();
	g_pApp->Finalize();

	delete g_pGraphicsManager;
	delete g_pInputManager;
	delete g_pAssetLoader;
	delete g_pAssetManager;
	delete g_pMemoryManager;

	return 0;
}
