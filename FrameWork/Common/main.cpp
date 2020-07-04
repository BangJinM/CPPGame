#include <iostream>
#include "IApplication.h"
#include "MemoryManager.h"
#include "InputManager.h"
#include "AssetLoader.h"
#include "GraphicsManager.h"
using namespace GameEngine;

namespace GameEngine
{
	extern IApplication *g_pApp;
	extern MemoryManager *g_pMemoryManager;
	extern InputManager *g_pInputManager;
	extern AssetLoader *g_pAssetLoader;
	extern GraphicsManager *g_pGraphicsManager;
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

	if ((ret == g_pGraphicsManager->Initialize()) != 0)
	{
		printf("App Initialize failed, will exit now.");
		return ret;
	}
	int i = 1;
	while (!g_pApp->IsQuit())
	{

		try
		{
			g_pMemoryManager->Tick();
			g_pInputManager->Tick();
			g_pAssetLoader->Tick();
			g_pApp->Tick();
			printf("%d\n", i++);
			g_pGraphicsManager->Tick();
		}
		catch (const std::exception&)
		{

		}
	}
	g_pGraphicsManager->Finalize();
	g_pInputManager->Finalize();
	g_pAssetLoader->Finalize();
	g_pMemoryManager->Finalize();
	g_pApp->Finalize();

	return 0;
}
