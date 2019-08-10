#include <iostream>

#include "Common/GamePlatform-opengl.h"

extern GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540);
extern OpenGLApplication  g_App(config);
IApplication*       g_pApp = &g_App;

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		printf(argv[i]);

	int ret;

	if ((ret = g_pApp->Initialize()) != 0) {
		printf("App Initialize failed, will exit now.");
		return ret;
	}

	while (!g_pApp->IsQuit()) {
		g_pApp->Tick();
	}

	g_pApp->Finalize();
	return 0;
}
